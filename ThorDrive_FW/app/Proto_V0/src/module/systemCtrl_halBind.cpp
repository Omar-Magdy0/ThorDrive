#include "systemCtrl_halBind.h"


using namespace modm::platform;

void systemCtrl_t::periph_init(){
    Ctrl_Led::setOutput(Gpio::OutputType::PushPull);
    Ctrl_Btn::setInput(Gpio::InputType::Floating);
}

void systemCtrl_t::ctrlLED_write(uint8_t logic)
{
    Ctrl_Led::set(logic);
}

bool systemCtrl_t::ctrlButt_read()
{
    return Ctrl_Btn::read();
}
