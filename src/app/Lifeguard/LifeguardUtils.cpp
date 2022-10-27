#include "LifeguardUtils.h"

/*
    @brief
    *
    * Create object
    * Params: Object to base on, object to base on alignment
    * Premade config
    *
*/
lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res( NULL ), 30);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, SETUP_STYLE  );
    lv_obj_align(obj, alignObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0 );
    return obj;
}
/*
    @brief
    *
    * Create text area
    * Params: Object to base on, value of variable, event to base on e.g LifeguardTextAreaEventCb
    * Premade config
    * 
*/
lv_obj_t * CreateTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event)
{
    lv_obj_t * textfield = lv_textarea_create( baseObj, NULL);
    lv_textarea_set_text(textfield, value);
    lv_textarea_set_pwd_mode(textfield, false);
    lv_textarea_set_one_line(textfield, true);
    lv_obj_set_width( textfield, lv_disp_get_hor_res( NULL ) / 4 * 3  - 5 );
    lv_obj_align( textfield, baseObj, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( textfield, event);
    return textfield;
}

/*
    @brief
    *
    * Create label
    * Params: Object to base on, text char
    * Premade config
    * 
*/
void CreateLabel(lv_obj_t * baseObj, char name[])
{
    lv_obj_t * label = lv_label_create( baseObj, NULL );
    lv_obj_add_style(label, LV_OBJ_PART_MAIN, SETUP_STYLE);
    lv_label_set_text(label, name);
    lv_obj_align(label, baseObj, LV_ALIGN_IN_LEFT_MID, 0, 0 );
}