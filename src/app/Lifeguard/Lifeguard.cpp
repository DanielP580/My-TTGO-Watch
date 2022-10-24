#include "config.h"
#include "quickglui/quickglui.h"

#include "Lifeguard.h"

#include "gui/mainbar/mainbar.h"
#include "gui/widget_styles.h"
#include "hardware/motor.h"
#include "hardware/motion.h"

//App icon
LV_IMG_DECLARE(Lifeguard_64px);

//Options mem
static String number, emergencyTime_s;

static SynchronizedApplication lifeGuardApp;
static JsonConfig config("lifeGuard.json");

void SetupMainPage()
{
    //Parent of widgets
    AppPage& screen = lifeGuardApp.mainPage();
}

void SetupSettings()
{
    config.addString("Number to call", 9, "").setDigitsMode(true, "0123456789").assign(&number);
    config.addString("Emergency time", 3, "10").setDigitsMode(true, "0123456789").assign(&emergencyTime_s);

    lifeGuardApp.useConfig(config, true);
}

//Initialize routine for app
void LifeguardAppSetup( void ) 
{
    //Initialize app
    lifeGuardApp.init("lifeGuardApp", &Lifeguard_64px, 1, 1);

    SetupMainPage();
    SetupSettings();
}
