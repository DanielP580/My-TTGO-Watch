#include "config.h"

#include "Lifeguard.h"
#include "LifeguardSetup.h"
#include "config/LifeguardConfig.h"
#include "LifeguardUtils.h"

//Tile definition
lv_obj_t * lifeguardSetupTile = NULL;

//Textfields definiton
lv_obj_t * lifeguardNumber_textfield = NULL;
lv_obj_t * lifeguardEmergencyTime_textfield = NULL;
lv_obj_t * lifeguardSensCalib_textfield = NULL;

//Function prototypes
static void LifeguardTextAreaEventCb(lv_obj_t * obj, lv_event_t event);
static void LifeguardNumTextAreaEventCb(lv_obj_t * obj, lv_event_t event);
static void LifeguardSetupHibernateCallback(void);

/*
    /brief
    *
    * Function to Setup Tile Setup
    *
*/
void LifeguardSetupTileSetup(uint32_t tileNum)
{
    //In setup get config
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();

    //Use function when hibernation occurs
    mainbar_add_tile_hibernate_cb( tileNum, LifeguardSetupHibernateCallback);

    //Use new tile num and based on that create new object
    lifeguardSetupTile = mainbar_get_tile_obj( tileNum);

    //Text objects
    char buffer[100]; 
    //Add header to top of settings 
    lv_obj_t * header = wf_add_settings_header( lifeguardSetupTile, "lifeguard setup");
    lv_obj_align(header, lifeguardSetupTile, LV_ALIGN_IN_TOP_MID, THEME_ICON_PADDING, THEME_ICON_PADDING);

    //Number line definitions
    lv_obj_t * lifeGuardNumber_obj = CreateListObject( lifeguardSetupTile, header);
    char numberName[] = "Number";
    CreateListLabel(lifeGuardNumber_obj, numberName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    lifeguardNumber_textfield = CreateListTextarea(lifeGuardNumber_obj, lifeguardConfig->number, LifeguardNumTextAreaEventCb);

    //EmergencyTime line definitions
    lv_obj_t * lifeGuardEmergencyTime_obj = CreateListObject( lifeguardSetupTile, lifeGuardNumber_obj);
    char emergencyTimeName[] = "Emergency\ntime";
    CreateListLabel(lifeGuardEmergencyTime_obj, emergencyTimeName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    sprintf(buffer, "%d", lifeguardConfig->emergencyTime);
    lifeguardEmergencyTime_textfield = CreateListTextarea(lifeGuardEmergencyTime_obj, buffer, LifeguardNumTextAreaEventCb);

    //EmergencyTime line definitions
    lv_obj_t * lifeGuardSensCalib_obj = CreateListObject( lifeguardSetupTile, lifeGuardEmergencyTime_obj);
    char emergencySensCalibName[] = "Sens\ncalib";
    CreateListLabel(lifeGuardSensCalib_obj, emergencySensCalibName, LV_ALIGN_IN_LEFT_MID, SETUP_STYLE);
    
    sprintf(buffer, "%d",lifeguardConfig->sensCalib);
    lifeguardSensCalib_textfield = CreateListTextarea(lifeGuardSensCalib_obj, buffer, LifeguardNumTextAreaEventCb);

    //Add elements to tile
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardNumber_obj);
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardEmergencyTime_obj);
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardSensCalib_obj);
}

/*
    /brief
    *
    * Function to hide keyboard and save configs when hibernation occurs
    *
*/
static void LifeguardSetupHibernateCallback(void)
{
    keyboard_hide();
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();
    strncpy( lifeguardConfig->number, lv_textarea_get_text( lifeguardNumber_textfield), sizeof(lifeguardConfig->number));
    lifeguardConfig->emergencyTime = atoi(lv_textarea_get_text( lifeguardEmergencyTime_textfield));
    lifeguardConfig->sensCalib = atoi(lv_textarea_get_text(lifeguardSensCalib_textfield));
    lifeguardConfig->save();
}

/* 
    /brief
    *
    * Function to activate keyboard from text area
    * 
*/
static void LifeguardTextAreaEventCb(lv_obj_t * obj, lv_event_t event)
{
    switch(event)
    {
        case (LV_EVENT_CLICKED): 
            keyboard_set_textarea(obj);
            break;
    }
}


/* 
    /brief
    *
    * Function to activate keyboard from number text area
    * 
*/
static void LifeguardNumTextAreaEventCb(lv_obj_t * obj, lv_event_t event) {
    switch(event)
    {
        case (LV_EVENT_CLICKED): 
            num_keyboard_set_textarea(obj);
            break;
    }
}