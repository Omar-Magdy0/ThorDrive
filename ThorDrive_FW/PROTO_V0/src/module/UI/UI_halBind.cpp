#include "Hal/Hal.h"
#include "UI.h"

using CtrlBtn = Gpio::Pin<CTRL_BTN_PinNum, CTRL_BTN_INVERT>;
using CtrlLed = Gpio::Pin<CTRL_LED_PinNum, CTRL_LED_INVERT>;

void UI::PeriphInit(){
    CtrlBtn::SetInput(Gpio::InputType::Floating);
    CtrlLed::SetOutput(Gpio::OutputType::PushPull);
}

void UI::CtrlLedWrite(bool logic)
{  
    CtrlLed::Write(logic);
}

bool UI::CtrlButtRead()
{
    return CtrlBtn::Read();
}
