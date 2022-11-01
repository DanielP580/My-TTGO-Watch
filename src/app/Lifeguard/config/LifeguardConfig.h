#ifndef _LIFEGUARDCONFIG_H
    #define _LIFEGUARDCONFIG_H

    #include "utils/basejsonconfig.h"

    #define LIFEGUARD_JSON_CONFIG_FILE "/lifeguard.json"

    class lifeguardConfig_t : public BaseJsonConfig {
        public:
            lifeguardConfig_t();
            char number[10];
            int32_t emergencyTime;
            int32_t sensCalib;

        protected:
            virtual bool onLoad(JsonDocument& document);
            virtual bool onSave(JsonDocument& document);
            virtual bool onDefault(void);
            virtual size_t getJsonBufferSize() { return 1000; }
    };

#endif // _LIFEGUARDCONFIG_H