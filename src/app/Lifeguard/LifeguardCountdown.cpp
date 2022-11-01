#include "config.h"
#include "quickglui/quickglui.h"

#include "LifeguardCountdown.h"
#include "Lifeguard.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"

#include "utils/json_psram_allocator.h"
#include "utils/alloc.h"

static uint32_t lifeguardCountdownTile_num;
lv_obj_t * lifeguardCountdownTile = NULL;
lv_obj_t * lifeguardCountdown_label = NULL;
lv_obj_t * lifeguardCountdownStart_btn = NULL;
lv_obj_t * lifeguardCountdownStop_btn = NULL;

//gui/font
LV_FONT_DECLARE(Ubuntu_16px);
LV_FONT_DECLARE(Ubuntu_72px);

lv_style_t lifeguardMainCountdown_style;

lv_task_t * lifeguardCountDown_task = NULL;

long countDown_s = 0;
static time_t prevTime;

static int brightness;

static void StopLifeguardCountdown(lv_obj_t * obj, lv_event_t event);
static void StartLifeguardCountdown(lv_obj_t * obj, lv_event_t event);
static void UpdateLifeguardCountDown();
void LifeguardCountDownTask(lv_task_t * task);
static void ShowCountdown();
static void StopCountdown();
static void CloseCountdown();
static void ResetLifeguardCountDown();

void LifeguardCountdownTileSetup(void)
{
    lifeguardCountdownTile_num = mainbar_add_app_tile(1, 1, "Countdown");
    lifeguardCountdownTile = mainbar_get_tile_obj( lifeguardCountdownTile_num);

    lv_style_copy( &lifeguardMainCountdown_style, APP_STYLE );
    lv_style_set_text_font( &lifeguardMainCountdown_style, LV_STATE_DEFAULT, &Ubuntu_72px);

    //Countdown definitions
    lv_obj_t * lifeguardCountdown_obj = CreateCenterObject( lifeguardCountdownTile, NULL, SETUP_STYLE);
    char defaultText[] = "00";
    lifeguardCountdown_label = CreateListLabel(lifeguardCountdown_obj, defaultText, LV_ALIGN_CENTER, &lifeguardMainCountdown_style);

    //lifeguardCountdownStart_btn = wf_add_play_button(lifeguardCountdownTile, StartLifeguardCountdown, SYSTEM_ICON_STYLE);
    //lv_obj_align(lifeguardCountdownStart_btn, lifeguardCountdownTile, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lifeguardCountdownStop_btn = wf_add_stop_button(lifeguardCountdownTile, StopLifeguardCountdown, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardCountdownStop_btn, lifeguardCountdownTile, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    lv_tileview_add_element( lifeguardCountdownTile, lifeguardCountdown_obj);

    ResetLifeguardCountDown();
    ResetLifeguardBMAFallStatus();
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
    lv_disp_trig_activity(NULL);
    display_set_brightness(DISPLAY_MAX_BRIGHTNESS);
    powermgm_set_event( POWERMGM_WAKEUP_REQUEST );
    mainbar_jump_to_tilenumber( lifeguardCountdownTile_num, LV_ANIM_OFF, true);
    lifeguardCountDown_task = lv_task_create(LifeguardCountDownTask, 1000, LV_TASK_PRIO_MID, NULL);
}

static void StopLifeguardCountdown( lv_obj_t * obj, lv_event_t event ) 
{
    switch( event ) {
        case( LV_EVENT_CLICKED ):
            StopCountdown();
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
    CreateBMATask();
    lv_task_del(lifeguardCountDown_task);
    display_set_brightness(brightness);
    ResetLifeguardCountDown();
    ResetLifeguardBMAFallStatus();
    mainbar_jump_back();
    
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
    int prevcountDown_s = countDown_s;
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