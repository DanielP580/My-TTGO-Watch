#include "config.h"

#include "Lifeguard_app.h"
#include "Lifeguard_app_main.h"

#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "gui/app.h"
#include "gui/widget.h"

uint32_t Lifeguard_app_main_tile_num;

icon_t *Lifeguard_app = NULL;
LV_IMG_DECLARE(Lifeguard_64px);

void Lifeguard_app_setup( void ) {
        Lifeguard_app_main_tile_num = mainbar_add_app_tile( 2, 1, "Lifeguard" );
        Lifeguard_app = app_register( "Lifeguard", &Lifeguard_64px, Lifeguard_app_enter_event_cb );
        Lifeguard_app_main_setup(Lifeguard_app_main_tile_num);
}

uint32_t Lifeguard_app_get_main_tile_num( void ) {
    return( Lifeguard_app_main_tile_num );
}

void Lifeguard_app_enter_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_tilenumber( Lifeguard_app_main_tile_num, LV_ANIM_OFF, true );
                                        app_hide_indicator( Lifeguard_app );
                                        break;
    }    
}

void exit_Lifeguard_app_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_back();
                                        break;
    }
}