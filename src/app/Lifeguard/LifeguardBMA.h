#ifndef  _LIFEGUARD_BMA_SETUP_H
    #define  _LIFEGUARD_BMA_SETUP_H

    void LifeguardBMATileSetup(uint32_t tileNum);
    bool GetLifeguardBMAFallStatus();
    void CreateBMATask();
    void KillBMATask();
    void ResetLifeguardBMAFallStatus();

#endif // _LIFEGUARD_BMA_SETUP_H