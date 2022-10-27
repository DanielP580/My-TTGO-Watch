#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "LifeguardConfig.h"

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
icon_t *lifeguardApp_Icon = NULL;

//app tile number
uint32_t lifeguardApp_MainTileNum;

//callback function
static void EnterLifeguardAppEventCb( lv_obj_t * obj, lv_event_t event);

//Initialize routine for app
void LifeguardAppSetup( void ) 
{
    lifeguardConfig.load();

    lifeguardApp_MainTileNum = mainbar_add_app_tile( 1, 1, "lifeguardApp");

    lifeguardApp_Icon = app_register( "lifeguard\nApp", &Lifeguard_64px, EnterLifeguardAppEventCb);
}

//Return number of lifeguardApp tile
uint32_t GetLifeguardApp_MainTileNum( void )
{
    return lifeguardApp_MainTileNum;
}

//return lifeguardApp icon
icon_t * GetLifeguardApp_Icon( void )
{
    return lifeguardApp_Icon;
}

lifeguardConfig_t *GetLifeguardConfig( void )
{
    return &lifeguardConfig;
}

/*
    /brief
    The idea is to create a button to jump into new tile
*/
static void EnterLifeguardAppEventCb( lv_obj_t * obj, lv_event_t event)
{
    switch( event )
    {
        case ( LV_EVENT_CLICKED ): mainbar_jump_to_tilenumber( lifeguardApp_MainTileNum, LV_ANIM_OFF, true); break;
    }
}