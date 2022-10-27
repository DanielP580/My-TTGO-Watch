#ifndef  _LIFEGUARD_APP_MAIN_H
    #define  _LIFEGUARD_APP_MAIN_H

    #include "LifeguardConfig.h"
    
    void LifeguardAppSetup( void );
    uint32_t GetLifeguardApp_MainTileNum( void );
    icon_t * GetLifeguardApp_Icon( void );
    lifeguardConfig_t *GetLifeguardConfig( void );

#endif //  _LIFEGUARD_APP_MAIN_H