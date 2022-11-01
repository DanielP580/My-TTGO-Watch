#include "config.h"
#include "quickglui/quickglui.h"

#include "LifeguardCountdown.h"
#include "Lifeguard.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"

#include "utils/json_psram_allocator.h"
#include "utils/alloc.h"

#define TURN_ON_COUNTDOWN 10
#define TURN_OFF_COUNTDOWN 0

static uint32_t lifeguardCountdownTile_num;
lv_obj_t * lifeguardCountdownTile = NULL;
lv_obj_t * lifeguardCountdown_label = NULL;
lv_obj_t * lifeguardCountdownStop_btn = NULL;
lv_obj_t * lifeguardCountdownStop_slider = NULL;

//gui/font
LV_FONT_DECLARE(Ubuntu_16px);
LV_FONT_DECLARE(Ubuntu_72px);

lv_style_t lifeguardMainCountdown_style;

lv_task_t * lifeguardCountDown_task = NULL;

long countDown_s = 0;
static time_t prevTime;

static int brightness;

bool isCountdown = false;;

static void StopLifeguardCountdown(lv_obj_t * obj, lv_event_t event);
static void UpdateLifeguardCountDown();
void LifeguardCountDownTask(lv_task_t * task);
static void ShowCountdown();
static void StopCountdown();
static void CloseCountdown();
static void ResetLifeguardCountDown();
void LifeguardCountdownStopSliderEventCb(lv_obj_t *brightness_slider, lv_event_t event);
void LifeguardCountdownResetSlider();

void LifeguardCountdownTileSetup(void)
{
    lifeguardCountdownTile_num = mainbar_add_app_tile(1, 1, "Countdown");
    lifeguardCountdownTile = mainbar_get_tile_obj( lifeguardCountdownTile_num);

    lv_style_copy(&lifeguardMainCountdown_style, APP_STYLE );
    lv_style_set_text_font(&lifeguardMainCountdown_style, LV_STATE_DEFAULT, &Ubuntu_72px);

    //Countdown definitions
    lv_obj_t * lifeguardCountdown_obj = CreateObject(lifeguardCountdownTile, NULL, LV_ALIGN_CENTER, APP_STYLE);
    char defaultText[] = "00";
    lifeguardCountdown_label = CreateListLabel(lifeguardCountdown_obj, defaultText, LV_ALIGN_CENTER, &lifeguardMainCountdown_style);

    lifeguardCountdownStop_btn = wf_add_stop_button(lifeguardCountdownTile, StopLifeguardCountdown, SYSTEM_ICON_STYLE);
    lv_obj_align(lifeguardCountdownStop_btn, lifeguardCountdownTile, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t * lifeguardCountdownStopSlider_obj = CreateObject(lifeguardCountdownTile, NULL, LV_ALIGN_IN_BOTTOM_MID, APP_STYLE);
    lifeguardCountdownStop_slider = CreateSlider(lifeguardCountdownStopSlider_obj, LV_ALIGN_IN_BOTTOM_MID, TURN_OFF_COUNTDOWN, TURN_ON_COUNTDOWN);
    lv_obj_set_event_cb(lifeguardCountdownStop_slider, LifeguardCountdownStopSliderEventCb);

    lv_tileview_add_element(lifeguardCountdownTile, lifeguardCountdownStopSlider_obj);
    lv_tileview_add_element(lifeguardCountdownTile, lifeguardCountdown_obj);

    ResetLifeguardCountDown();
    ResetLifeguardBMAFallStatus();
    LifeguardCountdownResetSlider();
}

void LifeguardCountdownResetSlider()
{
    lv_slider_set_value(lifeguardCountdownStop_slider, TURN_ON_COUNTDOWN, LV_ANIM_OFF);
}

void LifeguardCountdownStopSliderEventCb(lv_obj_t * obj, lv_event_t event)
{
    switch( event )
    {
        case (LV_EVENT_VALUE_CHANGED): 
            if(TURN_OFF_COUNTDOWN == lv_slider_get_value(obj))
            {
                StopCountdown();
            }
            break;
    }
}

void StartCountdown()
{
    if (!lifeguardCountDown_task)
    {
        powermgm_set_event(POWERMGM_WAKEUP_REQUEST);
        ResetLifeguardCountDown();
        brightness = display_get_brightness();
        mainbar_jump_to_tilenumber(lifeguardCountdownTile_num, LV_ANIM_OFF, true);
        isCountdown = true;
        lv_disp_trig_activity(NULL);
        display_set_brightness(DISPLAY_MAX_BRIGHTNESS);
        time(&prevTime);
        lifeguardCountDown_task = lv_task_create(LifeguardCountDownTask, 1000, LV_TASK_PRIO_MID, NULL);
    }
}

bool GetCountdownStatus()
{
    return isCountdown;
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
    if(lifeguardCountDown_task)
    {
        lv_task_del(lifeguardCountDown_task);
        lifeguardCountDown_task = NULL;
        display_set_brightness(brightness);
        ResetLifeguardCountDown();
        isCountdown = false;
        ResetLifeguardBMAFallStatus();
        mainbar_jump_back();
        LifeguardCountdownResetSlider();
    }
}

static void ResetLifeguardCountDown()
{
    lifeguardConfig_t * lifeguardConfig = GetLifeguardConfig();
    countDown_s = lifeguardConfig->emergencyTime;

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
    double diffTime_s = difftime(currentTime, prevTime);
    countDown_s = countDown_s - diffTime_s;
    prevTime = currentTime;

    UpdateLifeguardCountDown();
    motor_vibe(10, true);
    //sound_play_progmem_wav(piep_wav, piep_wav_len);

    if (countDown_s <= 0)
    {
        StopCountdown();
    }
}
