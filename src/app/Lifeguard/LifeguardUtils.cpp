#include "LifeguardUtils.h"

/*
    @brief
    *
    * Create object
    * Params: Object to base on, object to base on alignment
    * Premade config
    *
*/
lv_obj_t * CreateListObject(lv_obj_t * tileObj, lv_obj_t * alignObj)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res( NULL ), 37);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, SETUP_STYLE);
    lv_obj_align(obj, alignObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
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
lv_obj_t * CreateListTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event)
{
    lv_obj_t * textfield = lv_textarea_create( baseObj, NULL);
    lv_textarea_set_text(textfield, value);
    lv_textarea_set_pwd_mode(textfield, false);
    lv_textarea_set_one_line(textfield, true);
    lv_obj_set_width( textfield, lv_disp_get_hor_res( NULL ) / 4 * 1.5);
    lv_obj_align( textfield, baseObj, LV_ALIGN_IN_RIGHT_MID, -20, 0 );
    lv_obj_set_event_cb( textfield, event);
    return textfield;
}

/*
    @brief
    *
    * Create label
    * Params: Object to base on, text char, alignment, style object
    * 
*/
lv_obj_t * CreateListLabel(lv_obj_t * baseObj, char name[], lv_align_t align, lv_style_t * style)
{
    lv_obj_t * label = lv_label_create( baseObj, NULL );
    lv_obj_add_style(label, LV_OBJ_PART_MAIN, style);
    lv_label_set_text(label, name);
    lv_obj_align(label, baseObj, align, 0, 0 );
    return label;
}


/*
    @brief
    *
    * Create centered object
    * Params: Object to base on, object to base on alignment
    * Premade config
    *
*/
lv_obj_t * CreateCenterObject(lv_obj_t * tileObj, lv_obj_t * alignObj, lv_style_t * style)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res( NULL ), lv_disp_get_ver_res( NULL) / 2);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    lv_obj_align(obj, alignObj, LV_ALIGN_CENTER, 0, 0);
    return obj;
}
