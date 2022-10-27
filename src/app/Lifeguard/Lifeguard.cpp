#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "config/LifeguardConfig.h"
#include "LifeguardSetup.h"
#include "LifeguardMain.h"

#include "gui/mainbar/mainbar.h"
#include "gui/widget_styles.h"
#include "gui/statusbar.h"
#include "gui/app.h"
#include "gui/widget.h"
#include "hardware/motor.h"
#include "hardware/motion.h"

#include "utils/json_psram_allocator.h"

//App config
lifeguardConfig_t lifeguardConfig;

//App image 64x64px
LV_IMG_DECLARE(Lifeguard_64px);

//app icon
icon_t * lifeguard_icon = NULL;

//app tile number
uint32_t lifeguardMainTile_num;
uint32_t lifeguardSetupTile_num;

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

    lifeguard_icon = app_register("lifeguard\nApp", &Lifeguard_64px, EnterLifeguardAppEventCb);

    LifeguardMainTileSetup(lifeguardMainTile_num);
    LifeguardSetupTileSetup(lifeguardSetupTile_num);
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