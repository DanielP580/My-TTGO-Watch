#include "config.h"

#include "Lifeguard.h"
#include "LifeguardSetup.h"
#include "config/LifeguardConfig.h"

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
lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj);
void CreateLabel(lv_obj_t * baseObj, char name[]);
lv_obj_t * CreateTextarea(lv_obj_t * baseObj, char value[]);
lv_obj_t * CreateNumTextarea(lv_obj_t * baseObj, char value[]);

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
    lifeguardNumber_textfield = CreateNumTextarea(lifeGuardNumber_obj, lifeguardConfig->number);

    //EmergencyTime line definitions
    lv_obj_t * lifeGuardEmergencyTime_obj = CreateObject( lifeguardSetupTile, lifeGuardNumber_obj);
    char emergencyTimeName[] = "Emergency time";
    CreateLabel(lifeGuardEmergencyTime_obj, emergencyTimeName);
    lifeguardEmergencyTime_textfield = CreateNumTextarea(lifeGuardEmergencyTime_obj, lifeguardConfig->emergencyTime);

    //Add elements to tile
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardNumber_obj);
    lv_tileview_add_element( lifeguardSetupTile, lifeGuardEmergencyTime_obj);
}

lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res( NULL ), 30);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, SETUP_STYLE  );
    lv_obj_align(obj, alignObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0 );
    return obj;
}

void CreateLabel(lv_obj_t * baseObj, char name[])
{
    lv_obj_t * label = lv_label_create( baseObj, NULL );
    lv_obj_add_style(label, LV_OBJ_PART_MAIN, SETUP_STYLE);
    lv_label_set_text(label, name);
    lv_obj_align(label, baseObj, LV_ALIGN_IN_LEFT_MID, 0, 0 );
}

lv_obj_t * CreateNumTextarea(lv_obj_t * baseObj, char value[])
{
    lv_obj_t * textfield = lv_textarea_create( baseObj, NULL);
    lv_textarea_set_text(textfield, value);
    lv_textarea_set_pwd_mode(textfield, false);
    lv_textarea_set_one_line(textfield, true);
    lv_obj_set_width( textfield, lv_disp_get_hor_res( NULL ) / 4 * 3  - 5 );
    lv_obj_align( textfield, baseObj, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( textfield, LifeguardNumTextAreaEventCb);
    return textfield;
}

lv_obj_t * CreateTextarea(lv_obj_t * baseObj, char value[])
{
    lv_obj_t * textfield = lv_textarea_create( baseObj, NULL);
    lv_textarea_set_text(textfield, value);
    lv_textarea_set_pwd_mode(textfield, false);
    lv_textarea_set_one_line(textfield, true);
    lv_obj_set_width( textfield, lv_disp_get_hor_res( NULL ) / 4 * 3  - 5 );
    lv_obj_align( textfield, baseObj, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( textfield, LifeguardTextAreaEventCb);
    return textfield;
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

static void LifeguardNumTextAreaEventCb( lv_obj_t * obj, lv_event_t event ) {
    switch( event )
    {
        case ( LV_EVENT_CLICKED ): num_keyboard_set_textarea(obj);
    }
}