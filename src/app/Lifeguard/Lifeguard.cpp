#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "config/LifeguardConfig.h"
#include "LifeguardSetup.h"
#include "LifeguardMain.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"

//App config
lifeguardConfig_t lifeguardConfig;

//App image 64x64px
LV_IMG_DECLARE(Lifeguard_64px);

//app icon
icon_t * lifeguard_icon = NULL;

//app tile number
uint32_t lifeguardMainTile_num;
uint32_t lifeguardSetupTile_num;
uint32_t lifeguardBMATile_num;

//callback function
static void EnterLifeguardAppEventCb(lv_obj_t * obj, lv_event_t event);

/*
    /brief
    *
    * Function to Setup app
    *
*/
void LifeguardSetup(void) 
{
    lifeguardConfig.load();

    lifeguardMainTile_num = mainbar_add_app_tile(1, 1, "lifeguardApp");
    lifeguardSetupTile_num = mainbar_add_app_tile(1, 2, "lifeguardApp");
    lifeguardBMATile_num = mainbar_add_app_tile(1, 3, "lifeguardApp");

    lifeguard_icon = app_register("lifeguard\nApp", &Lifeguard_64px, EnterLifeguardAppEventCb);

    LifeguardMainTileSetup(lifeguardMainTile_num);
    LifeguardSetupTileSetup(lifeguardSetupTile_num);
    LifeguardBMATileSetup(lifeguardBMATile_num);
}

//Return number of lifeguardApp tile
uint32_t GetLifeguard_MainTileNum(void)
{
    return lifeguardMainTile_num;
}

//Return number of Setup tile
uint32_t GetLifeguard_SetupTileNum(void)
{
    return lifeguardSetupTile_num;
}

//Return number of BMA tile
uint32_t GetLifeguard_BMATileNum(void)
{
    return lifeguardBMATile_num;
}

//return lifeguard icon
icon_t * GetLifeguard_Icon(void)
{
    return lifeguard_icon;
}

lifeguardConfig_t * GetLifeguardConfig(void)
{
    return &lifeguardConfig;
}

/*
    /brief
    The idea is to create a button to jump into new tile
*/
static void EnterLifeguardAppEventCb(lv_obj_t * obj, lv_event_t event)
{
    switch(event)
    {
        case (LV_EVENT_CLICKED): mainbar_jump_to_tilenumber(lifeguardMainTile_num, LV_ANIM_OFF, true); break;
    }
}