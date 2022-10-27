#include "config.h"

#include "Lifeguard.h"
#include "LifeguardSetup.h"
#include "config/LifeguardConfig.h"
#include "LifeguardUtils.h"

#include "gui/mainbar/mainbar.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/statusbar.h"
#include "gui/keyboard.h"
#include "gui/widget_factory.h"
#include "gui/widget_styles.h"

//Tile definition
lv_obj_t * lifeguardSetupTile = NULL;
uint32_t lifeguardSetupTime_num;

//Textfields definiton
lv_obj_t * lifeguardNumber_textfield = NULL;
lv_obj_t * lifeguardEmergencyTime_textfield = NULL;

//Function prototypes
static void LifeguardTextAreaEventCb( lv_obj_t * obj, lv_event_t event);
static void LifeguardNumTextAreaEventCb( lv_obj_t * obj, lv_event_t event );
static void LifeguardSetupHibernateCallback ( void );

/*
    /brief
    *
    * Function to Setup Tile Setup
    *
*/
void LifeguardSetupTileSetup( uint32_t tileNum)
{
    //In setup get config
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();

    //Use function when hibernation occurs
    mainbar_add_tile_hibernate_cb( tileNum, LifeguardSetupHibernateCallback);

    //Use new tile num and based on that create new object
    lifeguardSetupTime_num = tileNum;
    lifeguardSetupTile = mainbar_get_tile_obj( lifeguardSetupTime_num);

    //Text objects

    //Add header to top of settings 
    lv_obj_t * header = wf_add_settings_header( lifeguardSetupTile, "lifeguard setup");
    lv_obj_align(header, lifeguardSetupTile, LV_ALIGN_IN_TOP_MID, THEME_ICON_PADDING, THEME_ICON_PADDING);

    //Number line definitions
    lv_obj_t * lifeGuardNumber_obj = CreateObject( lifeguardSetupTile, header);
    char numberName[] = "Number";
    CreateLabel(lifeGuardNumber_obj, numberName);
    lifeguardNumber_textfield = CreateTextarea(lifeGuardNumber_obj, lifeguardConfig->number, LifeguardNumTextAreaEventCb);

    //EmergencyTime line definitions
    lv_obj_t * lifeGuardEmergencyTime_obj = CreateObject( lifeguardSetupTile, lifeGuardNumber_obj);
    char emergencyTimeName[] = "Emergency time";
    CreateLabel(lifeGuardEmergencyTime_obj, emergencyTimeName);
    lifeguardEmergencyTime_textfield = CreateTextarea(lifeGuardEmergencyTime_obj, lifeguardConfig->emergencyTime, LifeguardNumTextAreaEventCb);

    //Add elements to tile
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardNumber_obj);
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardEmergencyTime_obj);
}

/*
    /brief
    *
    * Function to hide keyboard and save configs when hibernation occurs
    *
*/
static void LifeguardSetupHibernateCallback ( void )
{
    keyboard_hide();
    lifeguardConfig_t *lifeguardConfig = GetLifeguardConfig();
    strncpy( lifeguardConfig->number, lv_textarea_get_text( lifeguardNumber_textfield), sizeof(lifeguardConfig->number));
    strncpy( lifeguardConfig->emergencyTime, lv_textarea_get_text( lifeguardEmergencyTime_textfield), sizeof(lifeguardConfig->emergencyTime));
    lifeguardConfig->save();
}

/* 
    /brief
    *
    * Function to activate keyboard from text area
    * 
*/
static void LifeguardTextAreaEventCb( lv_obj_t * obj, lv_event_t event)
{
    switch( event )
    {
        case ( LV_EVENT_CLICKED ): keyboard_set_textarea(obj);
    }
}

/* 
    /brief
    *
    * Function to activate keyboard from number text area
    * 
*/
static void LifeguardNumTextAreaEventCb( lv_obj_t * obj, lv_event_t event ) {
    switch( event )
    {
        case ( LV_EVENT_CLICKED ): num_keyboard_set_textarea(obj);
    }
}