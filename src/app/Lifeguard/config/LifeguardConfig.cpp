#include "LifeguardConfig.h"

lifeguardConfig_t::lifeguardConfig_t() : BaseJsonConfig( LIFEGUARD_JSON_CONFIG_FILE) {}

bool lifeguardConfig_t::onSave(JsonDocument& doc){
    doc["lifeguard"]["number"] = number;
    doc["lifeguard"]["emergencyTime"] = emergencyTime_s;
    doc["lifeguard"]["sensTreshold"] = sensTreshold;
    doc["lifeguard"]["sensMinimal"] = sensMinimal;
    doc["lifeguard"]["tempMax"] = tempMax_tempC;
    doc["lifeguard"]["tempMin"] = tempMin_tempC;
    doc["lifeguard"]["maxTemperatureTime"] = maxTemperatureTime_s;
    doc["lifeguard"]["devMode"] = devMode;
    doc["lifeguard"]["maxfallTime"] = maxfallTime_ms;
    doc["lifeguard"]["minfallTime"] = minfallTime_ms;

    return true;
}

bool lifeguardConfig_t::onLoad(JsonDocument& doc){
    strncpy( number, doc["lifeguard"]["number"] | "123456789", sizeof(number));
    emergencyTime_s = doc["lifeguard"]["emergencyTime"] | 15;
    sensTreshold = doc["lifeguard"]["sensTreshold"] | 2000;
    sensMinimal = doc["lifeguard"]["sensMinimal"] | 1300;
    tempMax_tempC = doc["lifeguard"]["tempMax"] | 35;
    tempMin_tempC = doc["lifeguard"]["tempMin"] | 5;
    maxTemperatureTime_s = doc["lifeguard"]["maxTemperatureTime"] | 300;
    devMode = doc["lifeguard"]["devMode"] | true;
    maxfallTime_ms = doc["lifeguard"]["maxfallTime"] | 10000;
    minfallTime_ms = doc["lifeguard"]["minfallTime"] | 1000;
    
    return true;
}

void lifeguardConfig_t::Default(void){
    strncpy( number, "", sizeof(number));
    emergencyTime_s = 10;
    sensTreshold = 2000;
    sensMinimal = 1300;
    tempMax_tempC = 35;
    tempMin_tempC = 10;
    maxTemperatureTime_s = 300;
    devMode = false;
    maxfallTime_ms = 10000;
    minfallTime_ms = 3000;
}

bool lifeguardConfig_t::onDefault(void){
    strncpy( number, "", sizeof(number));
    emergencyTime_s = 10;
    sensTreshold = 2000;
    sensMinimal = 1300;
    tempMax_tempC = 35;
    tempMin_tempC = 10;
    maxTemperatureTime_s = 300;
    devMode = false;
    maxfallTime_ms = 10000;
    minfallTime_ms = 1000;

    return true;
}