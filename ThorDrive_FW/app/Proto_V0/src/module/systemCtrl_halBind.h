#include "systemCtrl.h"
#include "thorHal/hal.h"
#include "Config.h"
#include <modm/platform.hpp>

DEFINE_PIN(Ctrl_Btn, CTRL_BTN_PinNum, HALL_B_ON);
DEFINE_PIN(Ctrl_Led, CTRL_LED_PinNum, HALL_C_ON);
