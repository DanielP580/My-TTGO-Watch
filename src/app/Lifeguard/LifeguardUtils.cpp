#include "LifeguardUtils.h"

/**
    * @brief Create object
    * 
    * @param tileObj object to base on
    * @param alignObj object to base on alignment
    * 
    * @return object
*/
lv_obj_t * CreateListObject(lv_obj_t * tileObj, lv_obj_t * alignObj)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res(NULL), 25);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, SETUP_STYLE);
    lv_obj_align(obj, alignObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    return obj;
}

/**
    * @brief Create text area
    * 
    * @param baseObj object to base on
    * @param value set value of text area
    * @param event set event when typing text
    * 
    * @return textfield
*/
lv_obj_t * CreateListTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event)
{
    lv_obj_t * textfield = lv_textarea_create(baseObj, NULL);
    lv_textarea_set_text(textfield, value);
    lv_textarea_set_pwd_mode(textfield, false);
    lv_textarea_set_one_line(textfield, true);
    lv_obj_set_width(textfield, lv_disp_get_hor_res( NULL ) / 3);
    lv_obj_align(textfield, baseObj, LV_ALIGN_IN_RIGHT_MID, -70, 0);
    lv_obj_set_event_cb(textfield, event);
    return textfield;
}

/**
    * @brief Create label
    * 
    * @param baseObj object to base on
    * @param name set char name of label
    * @param align align define
    * @param style style object
    * 
    * @return label
*/
lv_obj_t * CreateListLabel(lv_obj_t * baseObj, char name[], lv_align_t align, lv_style_t * style)
{
    lv_obj_t * label = lv_label_create( baseObj, NULL );
    lv_obj_add_style(label, LV_OBJ_PART_MAIN, style);
    lv_label_set_text(label, name);
    lv_obj_align(label, baseObj, align, 0, 0 );
    return label;
}


/**
    * @brief Create centered object
    * 
    * @param tileObj object to base on
    * @param alignObj object to base on alignment
    * @param align align object
    * @param style style object
    * 
    * @return object
*/
lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj, lv_align_t align, lv_style_t * style)
{
    lv_obj_t * obj = lv_obj_create( tileObj, NULL);
    lv_obj_set_size(obj, lv_disp_get_hor_res( NULL ), lv_disp_get_ver_res( NULL) / 2);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    lv_obj_align(obj, alignObj, align, 0, 0);
    return obj;
}

/**
    * @brief Create centered object
    * 
    * @param tileObj object to base on
    * @param alignObj object to base on alignment
    * @param min minimum value of slider
    * @param max maximum value of slider
    * 
    * @return slider
*/
lv_obj_t * CreateSlider(lv_obj_t * tileObj, lv_align_t align, int16_t min, int16_t max)
{
    lv_obj_t * slider = lv_slider_create(tileObj, NULL);
    lv_obj_set_size(slider, lv_disp_get_hor_res(NULL) / 2, 40);
    lv_obj_align(slider, tileObj, align, 0, -40);
    lv_slider_set_range(slider, min, max);
    //lv_obj_add_protect(slider, LV_PROTECT_CLICK_FOCUS);
    //lv_obj_add_style(slider, LV_SLIDER_PART_INDIC, ws_get_slider_style());
    //lv_obj_add_style(slider, LV_SLIDER_PART_KNOB, ws_get_slider_style());
    return slider;
}
