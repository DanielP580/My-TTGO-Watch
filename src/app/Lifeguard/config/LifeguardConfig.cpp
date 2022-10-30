#include "LifeguardConfig.h"

lifeguardConfig_t::lifeguardConfig_t() : BaseJsonConfig( LIFEGUARD_JSON_CONFIG_FILE) {}

bool lifeguardConfig_t::onSave(JsonDocument& doc){
    doc["lifeguard"]["number"] = number;
    doc["lifeguard"]["emergencyTime"] = emergencyTime;
    doc["lifeguard"]["sensCalib"] = emergencyTime;

    return true;
}

bool lifeguardConfig_t::onLoad(JsonDocument& doc){
    strncpy( number, doc["lifeguard"]["number"] | "", sizeof(number));
    strncpy( emergencyTime, doc["lifeguard"]["number"] | "", sizeof(emergencyTime));
    sensCalib = doc["lifeguard"]["sensCalib"] | 50;

    return true;
}

bool lifeguardConfig_t::onDefault( void ){
    strncpy( number, "", sizeof(number));
    strncpy( emergencyTime, "", sizeof(emergencyTime));
    sensCalib = 50;

    return true;
}