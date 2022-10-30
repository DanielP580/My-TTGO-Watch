#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"
#include "LifeguardMain.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"

#include "utils/json_psram_allocator.h"
#include "utils/alloc.h"

lv_obj_t * lifeguardMainTile = NULL;
lv_obj_t * lifeguardExit_btn;
lv_obj_t * lifeguardSetup_btn;
lv_obj_t * lifeguardBMA_btn;
lv_obj_t * lifeguardCountdown_label;
lv_obj_t * lifeguardCountdownStart_btn;
lv_obj_t * lifeguardCountdownStop_btn;
lv_style_t lifeguardMainStyle;

//gui/font
LV_FONT_DECLARE(Ubuntu_16px);
LV_FONT_DECLARE(Ubuntu_72px);

lv_style_t lifeguardMainCountdown_style;

lv_task_t * lifeguardCountDown_task;

long countDown_s = 0;
static time_t prevTime;

static int brightness;

static void EnterLifeguardSetupEventCb(lv_obj_t * obj, lv_event_t event);
static void EnterLifeguardBMAEventCb(lv_obj_t * obj, lv_event_t event);
static void StopLifeguardCountdown(lv_obj_t * obj, lv_event_t event);
static void StartLifeguardCountdown(lv_obj_t * obj, lv_event_t event);
static void UpdateLifeguardCountDown();
void LifeguardCountDownTask(lv_task_t * task);
static void ShowCountdown();
static void StopCountdown();
static void CloseCountdown();
static void ResetLifeguardCountDown();

/*
    /brief
    *
    * Function to Setup Main tile
    *
*/
void LifeguardMainTileSetup( uint32_t tileNum)
{
    lifeguardMainTile = mainbar_get_tile_obj( tileNum);

    lv_style_copy( &lifeguardMainCountdown_style, APP_STYLE );
    lv_style_set_text_font( &lifeguardMainCountdown_style, LV_STATE_DEFAULT, &Ubuntu_72px);

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

    //Countdown definitions
    lv_obj_t * lifeguardCountdown_obj = CreateCenterObject( lifeguardMainTile, NULL, SETUP_STYLE);
    char defaultText[] = "00";
    lifeguardCountdown_label = CreateListLabel(lifeguardCountdown_obj, defaultText, LV_ALIGN_CENTER, &lifeguardMainCountdown_style);

    lifeguardCountdownStart_btn = wf_add_play_button(lifeguardMainTile, StartLifeguardCountdown, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardCountdownStart_btn, lifeguardMainTile, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lifeguardCountdownStop_btn = wf_add_stop_button(lifeguardMainTile, StopLifeguardCountdown, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardCountdownStop_btn, lifeguardMainTile, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    lv_tileview_add_element( lifeguardMainTile, lifeguardCountdown_obj);

    CloseCountdown();
}

static void EnterLifeguardSetupEventCb( lv_obj_t * obj, lv_event_t event ) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_tilenumber( GetLifeguard_SetupTileNum(), LV_ANIM_ON, true );
                                        break;
    }
}

static void EnterLifeguardBMAEventCb( lv_obj_t * obj, lv_event_t event ) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_tilenumber( GetLifeguard_BMATileNum(), LV_ANIM_ON, true );
                                        break;
    }
}

static void StartLifeguardCountdown( lv_obj_t * obj, lv_event_t event ) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):
            StartCountdown();
            break;
    }
}

void StartCountdown()
{
    brightness = display_get_brightness();
    powermgm_set_event( POWERMGM_WAKEUP_REQUEST );
    ResetLifeguardCountDown();
    ShowCountdown();
    lv_disp_trig_activity(NULL);
    display_set_brightness(DISPLAY_MAX_BRIGHTNESS);
    lifeguardCountDown_task = lv_task_create(LifeguardCountDownTask, 1000, LV_TASK_PRIO_HIGHEST, NULL);
}

static void StopLifeguardCountdown( lv_obj_t * obj, lv_event_t event ) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):
            StopCountdown();
            display_set_brightness(brightness);
            break;
    }
}

static void ShowCountdown()
{
    lv_obj_set_hidden(lifeguardCountdown_label, false); //countdown
    lv_obj_set_hidden(lifeguardCountdownStop_btn, false); //cancel countdown button
}

static void CloseCountdown()
{
    lv_obj_set_hidden(lifeguardCountdown_label, true); //countdown
    lv_obj_set_hidden(lifeguardCountdownStop_btn, true); //cancel countdown button
}

static void StopCountdown() 
{
    CloseCountdown();
    ResetLifeguardBMAFallStatus();
    lv_task_del(lifeguardCountDown_task);
}

static void ResetLifeguardCountDown()
{
    lifeguardConfig_t * lifeguardConfig = GetLifeguardConfig();
    countDown_s = atoi(lifeguardConfig->emergencyTime);

    UpdateLifeguardCountDown();
}

static void UpdateLifeguardCountDown()
{
    char countdownNum[5];

    //int countdownMin = (countDown_ms / 1000) / 60;
    int countdownSec = countDown_s % 60;

    sprintf(countdownNum, "%d", countdownSec);

    lv_label_set_text(lifeguardCountdown_label, countdownNum);
    lv_obj_align(lifeguardCountdown_label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void LifeguardCountDownTask(lv_task_t * task)
{
    time_t currentTime; 
    time(&currentTime);
    countDown_s -= difftime(currentTime, prevTime);
    prevTime = currentTime;

    UpdateLifeguardCountDown();
    motor_vibe( 10, true );
    //sound_play_progmem_wav(piep_wav, piep_wav_len);

    if (countDown_s <= 0)
    {
        StopCountdown();
    }
}


