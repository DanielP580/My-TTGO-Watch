#ifndef _LIFEGUARDCONFIG_H
    #define _LIFEGUARDCONFIG_H

    #include "utils/basejsonconfig.h"

    #define LIFEGUARD_JSON_CONFIG_FILE "/lifeguard.json"

    class lifeguardConfig_t : public BaseJsonConfig {
        public:
            lifeguardConfig_t();
            char number[10];
            int32_t emergencyTime_s = 10;
            int32_t sensTreshold = 2000;
            int32_t sensMinimal = 1300;
            int32_t tempMax_tempC = 35;
            int32_t tempMin_tempC = -5;
            int32_t maxTemperatureTime_s = 300;
            int32_t minfallTime_ms = 1000;
            int32_t maxfallTime_ms = 10000;
            bool devMode = false;

            virtual void Default();

        protected:
            virtual bool onLoad(JsonDocument& document);
            virtual bool onSave(JsonDocument& document);
            virtual bool onDefault(void);
            size_t getJsonBufferSize() { return 1000; }
    };

#endif // _LIFEGUARDCONFIG_H