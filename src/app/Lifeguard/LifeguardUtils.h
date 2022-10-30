#ifndef  _LIFEGUARD_UTILS_H
    #define  _LIFEGUARD_UTILS_H

    #include "config.h"
    #include "quickglui/quickglui.h"

    #include "gui/widget_factory.h"
    #include "gui/widget_styles.h"
    #include "gui/mainbar/mainbar.h"
    #include "gui/widget_styles.h"
    #include "gui/statusbar.h"
    #include "gui/app.h"
    #include "gui/widget.h"
    #include "hardware/motor.h"
    #include "hardware/motion.h"
    #include "gui/mainbar/main_tile/main_tile.h"
    #include "gui/keyboard.h"
    #include "utils/json_psram_allocator.h"

    lv_obj_t * CreateListObject(lv_obj_t * tileObj, lv_obj_t * alignObj);
    lv_obj_t * CreateListTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event);
    void CreateListLabel(lv_obj_t * baseObj, char name[]);
    lv_obj_t * CreateCenterObject(lv_obj_t * tileObj, lv_obj_t * alignObj, lv_style_t * style);
    lv_obj_t * CreateCenterLabel(lv_obj_t * baseObj, char name[], lv_style_t * style);

#endif //  _LIFEGUARD_UTILS_H