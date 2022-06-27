#ifndef  _LIFEGUARD_APP_MAIN_H
    #define  _LIFEGUARD_APP_MAIN_H

    #ifdef NATIVE_64BIT
        #include <string>
        using namespace std;
        #define String string
    #endif

    void Lifeguard_app_setup( void );
    uint32_t Lifeguard_app_get_main_tile_num( void );
    void Lifeguard_app_enter_event_cb( lv_obj_t * obj, lv_event_t event );
    void exit_Lifeguard_app_event_cb( lv_obj_t * obj, lv_event_t event );

#endif //  _LIFEGUARD_APP_MAIN_H