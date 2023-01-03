/****************************************************************************
 *   Jan 3 14:00 2023
 *   Copyright  2023  Daniel Podgorski
 *   Email: danielpodgorski@o2.pl
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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