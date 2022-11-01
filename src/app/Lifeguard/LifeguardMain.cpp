#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "LifeguardMain.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"
#include "LifeguardCountdown.h"

#include "utils/json_psram_allocator.h"
#include "utils/alloc.h"

lv_obj_t * lifeguardMainTile = NULL;
lv_obj_t * lifeguardExit_btn = NULL;
lv_obj_t * lifeguardSetup_btn = NULL;
lv_obj_t * lifeguardBMA_btn = NULL;
lv_obj_t * lifeguardCountdownStart_btn = NULL;
lv_style_t lifeguardMainStyle;

LV_FONT_DECLARE(Ubuntu_16px);

static void EnterLifeguardSetupEventCb(lv_obj_t * obj, lv_event_t event);
static void EnterLifeguardBMAEventCb(lv_obj_t * obj, lv_event_t event);
static void StartLifeguardCountdown(lv_obj_t * obj, lv_event_t event);

/*
    /brief
    *
    * Function to Setup Main tile
    *
*/
void LifeguardMainTileSetup(uint32_t tileNum)
{
    lifeguardMainTile = mainbar_get_tile_obj( tileNum);

    //Set tile style
    lv_style_copy( &lifeguardMainStyle, APP_STYLE);
    lv_style_set_text_font( &lifeguardMainStyle, LV_STATE_DEFAULT, &Ubuntu_16px);
    lv_obj_add_style( lifeguardMainTile, LV_OBJ_PART_MAIN, &lifeguardMainStyle );

    //Create buttons
    lv_obj_t * lifeguardExit_btn = wf_add_exit_button( lifeguardMainTile, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardExit_btn, lifeguardMainTile, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);

    lv_obj_t * lifeguardSetup_btn = wf_add_setup_button( lifeguardMainTile, EnterLifeguardSetupEventCb, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardSetup_btn, lifeguardMainTile, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);

    lv_obj_t * lifeguardBMA_btn = wf_add_setup_button( lifeguardMainTile, EnterLifeguardBMAEventCb, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardBMA_btn, lifeguardMainTile, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    lifeguardCountdownStart_btn = wf_add_play_button(lifeguardMainTile, StartLifeguardCountdown, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardCountdownStart_btn, lifeguardMainTile, LV_ALIGN_IN_RIGHT_MID, 0, 0);
}

static void StartLifeguardCountdown(lv_obj_t * obj, lv_event_t event) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):
            StartCountdown();
            break;
    }
}

static void EnterLifeguardSetupEventCb(lv_obj_t * obj, lv_event_t event) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
            mainbar_jump_to_tilenumber(GetLifeguard_SetupTileNum(), LV_ANIM_OFF, true );
            break;
    }
}

static void EnterLifeguardBMAEventCb(lv_obj_t * obj, lv_event_t event) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
            mainbar_jump_to_tilenumber(GetLifeguard_BMATileNum(), LV_ANIM_OFF, true );
            break;
    }
}


