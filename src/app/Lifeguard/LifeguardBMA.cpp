#include "LifeguardUtils.h"

#include "Lifeguard.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"
#include <inttypes.h> 

//Tile definition
lv_obj_t * lifeguardBMATile = NULL;

//Textfields definiton
lv_obj_t * lifeguardX_textfield = NULL;
lv_obj_t * lifeguardY_textfield = NULL;
lv_obj_t * lifeguardZ_textfield = NULL;

lv_obj_t * lifeguardX_label;
lv_obj_t * lifeguardY_label;
lv_obj_t * lifeguardZ_label;
lv_obj_t * lifeguardStatus_label;

Accel acceleration;
int X_accel;
int Y_accel;
int Z_accel;
char activity[23];

lv_task_t * lifeguardBMA_task;

static void SetupLifeguardBMA();
static void UpdateLifeguardBMAStatus();
void LifeguardBMATask(lv_task_t * task);

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

    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Xobj);
    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Yobj);
    lv_tileview_add_element( lifeguardBMATile, lifeGuardBMA_Zobj);

    SetupLifeguardBMA();
    
    lifeguardBMA_task = lv_task_create(LifeguardBMATask, 200, LV_TASK_PRIO_LOW, NULL);
}

static void SetupLifeguardBMA()
{
    TTGOClass *ttgo = TTGOClass::getWatch();
    ttgo->bma->begin();
    ttgo->bma->enableAccel(BMA4_ENABLE);
}

static void UpdateLifeguardBMAStatus()
{
    TTGOClass *ttgo = TTGOClass::getWatch();
    ttgo->bma->getAccel(acceleration);
 
    X_accel = int(acceleration.x);
    Y_accel = int(acceleration.y);
    Z_accel = int(acceleration.z);

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
    sprintf(activity, "%s", ttgo->bma->getActivity());

    lv_label_set_text(lifeguardStatus_label, activity);
    lv_obj_align(lifeguardStatus_label, NULL, LV_ALIGN_IN_LEFT_MID, 90, 0);

}

void LifeguardBMATask(lv_task_t * task)
{
    UpdateLifeguardBMAStatus();
}
