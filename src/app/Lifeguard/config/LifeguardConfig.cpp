#include "LifeguardConfig.h"

lifeguardConfig_t::lifeguardConfig_t() : BaseJsonConfig( LIFEGUARD_JSON_CONFIG_FILE) {}

bool lifeguardConfig_t::onSave(JsonDocument& doc){
    doc["lifeguard"]["number"] = number;
    doc["lifeguard"]["emergencyTime"] = emergencyTime;
    doc["lifeguard"]["sensCalib"] = sensCalib;

    return true;
}

bool lifeguardConfig_t::onLoad(JsonDocument& doc){
    strncpy( number, doc["lifeguard"]["number"] | "", sizeof(number));
    emergencyTime = doc["lifeguard"]["emergencyTime"] | 10;
    sensCalib = doc["lifeguard"]["sensCalib"] | 1500;
    
    return true;
}

bool lifeguardConfig_t::onDefault( void ){
    strncpy( number, "", sizeof(number));
    emergencyTime = 10;
    sensCalib = 1500;

    return true;
}