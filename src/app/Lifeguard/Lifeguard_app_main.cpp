#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lifeguard_app.h"
#include "Lifeguard_app_main.h"

#include "gui/mainbar/app_tile/app_tile.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "gui/widget_factory.h"
#include "gui/widget_styles.h"

lv_obj_t *Lifeguard_app_main_tile = NULL;

LV_FONT_DECLARE(Ubuntu_12px);
LV_FONT_DECLARE(Ubuntu_32px);

void Lifeguard_app_main_setup( uint32_t tile_num ) {

    Lifeguard_app_main_tile = mainbar_get_tile_obj( tile_num );

    lv_obj_t * exit_btn = wf_add_exit_button( Lifeguard_app_main_tile, exit_Lifeguard_app_event_cb );
    #if defined( ROUND_DISPLAY )
        lv_obj_align(exit_btn, Lifeguard_app_main_tile, LV_ALIGN_IN_BOTTOM_MID, -( THEME_ICON_SIZE / 2 ), -THEME_ICON_PADDING );
    #else
        lv_obj_align(exit_btn, Lifeguard_app_main_tile, LV_ALIGN_IN_BOTTOM_LEFT, THEME_ICON_PADDING, -THEME_ICON_PADDING );
    #endif

}