#ifndef  _LIFEGUARD_H
    #define  _LIFEGUARD_H

    #include "gui/icon.h"
    #include "config/LifeguardConfig.h"

    #define LIFEGUARD_JSON_CONFIG_FILE "/lifeguard.json"

    void LifeguardSetup(void);
    uint32_t GetLifeguard_MainTileNum(void);
    uint32_t GetLifeguard_SetupTileNum(void);
    uint32_t GetLifeguard_BMATileNum(void);
    icon_t * GetLifeguard_Icon(void);
    lifeguardConfig_t * GetLifeguardConfig(void);

#endif //  _LIFEGUARD_H