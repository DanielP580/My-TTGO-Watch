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

    lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj);
    lv_obj_t * CreateTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event);
    void CreateLabel(lv_obj_t * baseObj, char name[]);

#endif //  _LIFEGUARD_UTILS_H