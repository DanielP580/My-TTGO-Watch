#include "LifeguardUtils.h"

#include "Lifeguard.h"
#include "LifeguardBMA.h"
#include "LifeguardMain.h"
#include "LifeguardCountdown.h"
#include "config/LifeguardConfig.h"
#include "LifeguardUtils.h"
#include <inttypes.h> 
#include "hardware/motion.h"

#define BMA_TASK_PERIOD 100

//Tile definition
lv_obj_t * lifeguardBMATile = NULL;

//Textfields definiton
lv_obj_t * lifeguardX_textfield = NULL;
lv_obj_t * lifeguardY_textfield = NULL;
lv_obj_t * lifeguardZ_textfield = NULL;

lv_obj_t * lifeguardX_label = NULL;
lv_obj_t * lifeguardY_label = NULL;
lv_obj_t * lifeguardZ_label = NULL;
lv_obj_t * lifeguardStatus_label = NULL;
lv_obj_t * lifeguardTemperature_label = NULL;

Accel acceleration;
int X_accel;
int Y_accel;
int Z_accel;
int prevX_accel;
int prevY_accel;
int prevZ_accel;

char activity_c[23];
char tries_c[10];
char temperature_c[10];

int pressCount = 0;
int tries = 0;
int maxTries = 10;
float temperatureTime_s = 0;
float temperature = 0;

bool isFall = false;

lv_task_t * lifeguardBMA_task;

static void SetupLifeguardBMA();
static void UpdateLifeguardBMAStatus();
void LifeguardBMATask(lv_task_t * task);
bool LifeguardBMAActivityLoopCb(EventBits_t event, void *arg);
bool LifeguardBMAMotionLoopCb(EventBits_t event, void *arg);
static void LifeguardBMASendBluetoothMessage();
static void LifeguardBMACheckForFall();
static void LifeguardBMAUpdateObjects();

void LifeguardBMATileSetup(uint32_t tileNum)
{
    //Use new tile num and based on that create new object
    lifeguardBMATile = mainbar_get_tile_obj( tileNum);

    //Add header to top of settings 
    lv_obj_t * header = wf_add_settings_header( lifeguardBMATile, "lifeguard BMA");
    lv_obj_align(header, lifeguardBMATile, LV_ALIGN_IN_TOP_MID, THEME_ICON_PADDING, THEME_ICON_PADDING);

    char defaultName[] = "0";
    //X-axis definitions
    lv_obj_t * lifeGuardBMA_Xobj = CreateListObject( lifeguardBMATile, header);
    char xName[] = "X";
    CreateListLabel(lifeGuardBMA_Xobj, xName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardX_label = CreateListLabel(lifeGuardBMA_Xobj, defaultName, LV_ALIGN_CENTER, SETUP_STYLE);

    //Y-axis definitions
    lv_obj_t * lifeGuardBMA_Yobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_Xobj);
    char yName[] = "Y";
    CreateListLabel(lifeGuardBMA_Yobj, yName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardY_label = CreateListLabel(lifeGuardBMA_Yobj, defaultName, LV_ALIGN_CENTER, SETUP_STYLE);

    //Z-axis definitions
    lv_obj_t * lifeGuardBMA_Zobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_Yobj);
    char zName[] = "Z";
    CreateListLabel(lifeGuardBMA_Zobj, zName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardZ_label = CreateListLabel(lifeGuardBMA_Zobj, defaultName, LV_ALIGN_CENTER, SETUP_STYLE);

    //Status definitions
    lv_obj_t * lifeGuardBMA_statusobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_Zobj);
    char statusName[] = "Status";
    CreateListLabel(lifeGuardBMA_statusobj, statusName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardStatus_label = CreateListLabel(lifeGuardBMA_statusobj, defaultName, LV_ALIGN_CENTER, SETUP_STYLE);

    //Temperature definitions
    lv_obj_t * lifeGuardBMA_temperatureobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_statusobj);
    char triesName[] = "Temp";
    CreateListLabel(lifeGuardBMA_temperatureobj, triesName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardTemperature_label = CreateListLabel(lifeGuardBMA_temperatureobj, defaultName, LV_ALIGN_CENTER, SETUP_STYLE);

    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Xobj);
    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Yobj);
    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Zobj);
    lv_tileview_add_element( lifeguardBMATile, lifeguardStatus_label);
    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_temperatureobj);

    SetupLifeguardBMA();
    CreateBMATask();
}

static void SetupLifeguardBMA()
{
    bma423_anymotion_config anymotionconfig;
    TTGOClass *ttgo = TTGOClass::getWatch();    

    ttgo->bma->enableFeature(BMA423_ACTIVITY, 1);
    ttgo->bma->enableActivityInterrupt(BMA4_ENABLE);
    ttgo->bma->enableFeature(BMA423_ANY_MOTION, 1);
    ttgo->bma->enableAnyNoMotionInterrupt(BMA4_ENABLE);
    ttgo->bma->enableAccel(BMA4_ENABLE);
    

    //this part is not supported by official BMA library it will not work without modification
    anymotionconfig.nomotion_sel = BMA423_ALL_AXIS_EN;
    anymotionconfig.threshold = 4; //0.5 g
    anymotionconfig.duration = 1; //20ms movement
    //uses function that is not developed in bma423.h
    ttgo->bma->set_any_mo_config(&anymotionconfig);
    //this part is not supported by official BMA library it will not work without modificatio

    bma_register_cb(BMACTL_ACTIVITY, LifeguardBMAActivityLoopCb, "activity update");
    bma_register_cb(BMACTL_ACTIVITY, LifeguardBMAMotionLoopCb, "activity update");

    if (true == ttgo->bma->getAccel(acceleration))
    {
        prevX_accel = int(acceleration.x);
        prevY_accel = int(acceleration.y);
        prevZ_accel = int(acceleration.z);
    }
}

bool LifeguardBMAActivityLoopCb(EventBits_t event, void *arg)
{
    powermgm_set_event(POWERMGM_SILENCE_WAKEUP_REQUEST);
    lv_task_ready(lifeguardBMA_task);

    return true;
}

bool LifeguardBMAMotionLoopCb(EventBits_t event, void *arg)
{
    powermgm_set_event(POWERMGM_SILENCE_WAKEUP_REQUEST);
    lv_task_ready(lifeguardBMA_task);
    LifeguardCountdownStart();

    return true;
}

/**
    * @brief Create task for bma. It works only when powermgm is in POWERMGM_WAKEUP
*/
void CreateBMATask()
{
    lifeguardBMA_task = lv_task_create(LifeguardBMATask, BMA_TASK_PERIOD, LV_TASK_PRIO_HIGH, NULL);
}

void KillBMATask()
{
    lv_task_del(lifeguardBMA_task);
}

bool GetLifeguardBMAFallStatus()
{
    return isFall;
}

void ResetLifeguardBMAFallStatus()
{
    isFall = false;
}

static void UpdateLifeguardBMAStatus()
{
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();
    TTGOClass *ttgo = TTGOClass::getWatch();

    if (true == ttgo->bma->getAccel(acceleration))
    {
        X_accel = int(acceleration.x);
        Y_accel = int(acceleration.y);
        Z_accel = int(acceleration.z);  

        temperature = ttgo->bma->temperature();
    }

    LifeguardBMAUpdateObjects();
    LifeguardBMACheckForFall();
    LifeguardBMASendBluetoothMessage();
}

static void LifeguardBMAUpdateObjects()
{
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();
    TTGOClass *ttgo = TTGOClass::getWatch();

    char dir_accel[10];
    //X
    sprintf(dir_accel, "%d" , X_accel);
    lv_label_set_text(lifeguardX_label, dir_accel);
    lv_obj_align(lifeguardX_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);

    //Y
    sprintf(dir_accel, "%d", Y_accel);
    lv_label_set_text(lifeguardY_label, dir_accel);
    lv_obj_align(lifeguardY_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);

    //Z
    sprintf(dir_accel, "%d", Z_accel);
    lv_label_set_text(lifeguardZ_label, dir_accel);
    lv_obj_align(lifeguardZ_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);

    //activity
    sprintf(activity_c, "%s", ttgo->bma->getActivity());

    lv_label_set_text(lifeguardStatus_label, activity_c);
    lv_obj_align(lifeguardStatus_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);

    //temperature
    sprintf(temperature_c, "%8f", temperature);

    lv_label_set_text(lifeguardTemperature_label, temperature_c);
    lv_obj_align(lifeguardTemperature_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);
}

static void LifeguardBMACheckForFall()
{
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();

    if(!isFall && (sqrt(pow(X_accel - prevX_accel, 2) + pow(Y_accel - prevY_accel, 2 ) + pow(Z_accel - prevZ_accel, 2 )) >= lifeguardConfig->sensCalib))
    {
        isFall = true;
    }

    if(isFall && !GetCountdownStatus())
    {
        if(((0 == strncmp(activity_c,"BMA423_USER_STATIONARY", 23)) || (0 ==strncmp(activity_c,"None", 4))))
        {
            LifeguardCountdownStart();
        } 
        else if(++tries >= maxTries)
        {
            ResetLifeguardBMAFallStatus();
        }
    }

    if((temperature > lifeguardConfig->tempMax_tempC) || (temperature < lifeguardConfig->tempMin_tempC))
    {
        temperatureTime_s += BMA_TASK_PERIOD/1000;
        if (temperatureTime_s >= lifeguardConfig->maxTemperatureTime_s)
        {
            temperatureTime_s = 0;
            LifeguardCountdownStart();
        }
    }
    else
    {
        temperatureTime_s = 0;
    }

    prevX_accel = X_accel;
    prevY_accel = Y_accel;
    prevZ_accel = Z_accel;
}
static void LifeguardBMASendBluetoothMessage()
{
    blectl_send_msg( (char*)"\r\n{X:\"%d\", Y:\"%d\", Z:\"%d\", Ac:\"%s\", T:\"%s\"}\r\n", X_accel, Y_accel, Z_accel, activity_c, temperature_c);
}



void LifeguardBMATask(lv_task_t * task)
{
    UpdateLifeguardBMAStatus();
}