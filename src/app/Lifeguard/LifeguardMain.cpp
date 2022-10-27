#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "LifeguardMain.h"

#include "gui/mainbar/app_tile/app_tile.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/mainbar/mainbar.h"
#include "gui/widget_styles.h"
#include "gui/statusbar.h"
#include "gui/app.h"
#include "gui/widget.h"
#include "gui/widget_factory.h"
#include "gui/widget_styles.h"
#include "hardware/motor.h"
#include "hardware/motion.h"

#include "utils/json_psram_allocator.h"
#include "utils/alloc.h"

lv_obj_t * lifeguardMainTile = NULL;
lv_style_t lifeguardMainStyle;

LV_FONT_DECLARE(Ubuntu_16px);

static void EnterLifeguardSetupEventCb( lv_obj_t * obj, lv_event_t event);


/*
    /brief
    *
    * Function to Setup Main tile
    *
*/
void LifeguardMainTileSetup( uint32_t tileNum)
{
    lifeguardMainTile = mainbar_get_tile_obj( tileNum);

    //Set tile style
    lv_style_copy( &lifeguardMainStyle, APP_STYLE);
    lv_style_set_text_font( &lifeguardMainStyle, LV_STATE_DEFAULT, &Ubuntu_16px);
    lv_obj_add_style( lifeguardMainTile, LV_OBJ_PART_MAIN, &lifeguardMainStyle );

    //Create buttons
    lv_obj_t * exitButton = wf_add_exit_button( lifeguardMainTile, SYSTEM_ICON_STYLE);
    lv_obj_align(exitButton, lifeguardMainTile, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);

    lv_obj_t * setupButton = wf_add_setup_button( lifeguardMainTile, EnterLifeguardSetupEventCb, SYSTEM_ICON_STYLE);
    lv_obj_align(setupButton, lifeguardMainTile, LV_ALIGN_IN_BOTTOM_RIGHT, 10, -10);

}

static void EnterLifeguardSetupEventCb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_tilenumber( GetLifeguard_SetupTileNum(), LV_ANIM_ON, true );
                                        break;
    }
}


