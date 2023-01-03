/****************************************************************************
 *   Jan 3 14:00 2023
 *   Copyright  2023  Daniel Podgorski
 *   Email: danielpodgorski@o2.pl
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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
    #include "hardware/powermgm.h"
    #include "hardware/sound.h"
    #include "gui/sound/piep.h"
    #include "drive/bma423/bma.h"
    #include "hardware/display.h"
    #include "hardware/blectl.h"
    #include "hardware/callback.h"

    lv_obj_t * CreateListObject(lv_obj_t * tileObj, lv_obj_t * alignObj);
    lv_obj_t * CreateListTextarea(lv_obj_t * baseObj, char value[], lv_event_cb_t event);
    lv_obj_t * CreateListLabel(lv_obj_t * baseObj, char name[], lv_align_t align, lv_style_t * style);
    lv_obj_t * CreateObject(lv_obj_t * tileObj, lv_obj_t * alignObj, lv_align_t align, lv_style_t * style);
    lv_obj_t * CreateSlider(lv_obj_t * tileObj, lv_align_t align, int16_t min, int16_t max);

#endif //  _LIFEGUARD_UTILS_H