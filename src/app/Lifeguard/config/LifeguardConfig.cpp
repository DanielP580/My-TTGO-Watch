#include "LifeguardConfig.h"

lifeguardConfig_t::lifeguardConfig_t() : BaseJsonConfig( LIFEGUARD_JSON_CONFIG_FILE) {}

bool lifeguardConfig_t::onSave(JsonDocument& doc){
    doc["lifeguard"]["number"] = number;
    doc["lifeguard"]["emergencyTime"] = emergencyTime_s;
    doc["lifeguard"]["sensCalib"] = sensCalib;
    doc["lifeguard"]["tempMax"] = tempMax_tempC;
    doc["lifeguard"]["tempMin"] = tempMin_tempC;
    doc["lifeguard"]["maxTemperatureTime"] = maxTemperatureTime_s;
    doc["lifeguard"]["devMode"] = devMode;

    return true;
}

bool lifeguardConfig_t::onLoad(JsonDocument& doc){
    strncpy( number, doc["lifeguard"]["number"] | "123456789", sizeof(number));
    emergencyTime_s = doc["lifeguard"]["emergencyTime"] | 10;
    sensCalib = doc["lifeguard"]["sensCalib"] | 1500;
    tempMax_tempC = doc["lifeguard"]["tempMax"] | 35;
    tempMin_tempC = doc["lifeguard"]["tempMin"] | -5;
    maxTemperatureTime_s = doc["lifeguard"]["maxTemperatureTime"] | 300;
    devMode = doc["lifeguard"]["devMode"] | true;
    
    return true;
}

bool lifeguardConfig_t::onDefault( void ){
    strncpy( number, "", sizeof(number));
    emergencyTime_s = 10;
    sensCalib = 1500;
    tempMax_tempC = 35;
    tempMin_tempC = -5;
    maxTemperatureTime_s = 300;
    devMode = false;

    return true;
}