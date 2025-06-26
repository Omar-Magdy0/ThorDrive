#include "pmsmTrapCom_halBind.h"


using namespace modm::platform;

hallSensor_value hall_t::read(){
   hallSensor_value hallVal;
   hallVal.hallA = Hall_A::read();
   hallVal.hallB = Hall_B::read();
   hallVal.hallC = Hall_C::read();
   return hallVal;
}

void hall_t::periph_init(){
    Hall_A::setInput(Gpio::InputType::PullUp);
    Hall_B::setInput(Gpio::InputType::PullUp);
    Hall_C::setInput(Gpio::InputType::PullUp);
    Hall_A::enablePcInterrupt();
    Hall_B::enablePcInterrupt();
    Hall_C::enablePcInterrupt();
}

void pmsmTrapCom_t::periph_init(uint32_t swchFreq)
{
    Driver_Ah::setOutput(Gpio::OutputType::PushPull);
    Driver_Bh::setOutput(Gpio::OutputType::PushPull);
    Driver_Ch::setOutput(Gpio::OutputType::PushPull);
    Driver_Al::setOutput(Gpio::OutputType::PushPull);
    Driver_Bl::setOutput(Gpio::OutputType::PushPull);
    Driver_Cl::setOutput(Gpio::OutputType::PushPull);

    Driver_Ah::set(LOW);
    Driver_Bh::set(LOW);
    Driver_Ch::set(LOW);
    Driver_Al::set(LOW);
    Driver_Bl::set(LOW);
    Driver_Cl::set(LOW);

    Speed::setOutput(Gpio::OutputType::PushPull);
    Speed_TimPwm::init(SWITCHING_FREQ);
    Speed_Channel::init(SPEED_ON);

    effDuty_fixed_Max = Speed_TimPwm::getTimMax();
}

void pmsmTrapCom_t::driverWrite(pwmRes a, pwmRes b, pwmRes c, bool aSide, bool bSide, bool cSide)
{
    // Phase A
    /*pwmRes n  defines duty 0 for floating phase and effDuty_fixed_max as the maximum duty
    nSide determine which side of the half bridge is active
    */    
    Driver_Ah::set(a && aSide);
    Driver_Al::set(a && !aSide);

    Driver_Bh::set(b && bSide);
    Driver_Bl::set(b && !bSide);

    Driver_Ch::set(c && cSide);
    Driver_Cl::set(c && !cSide);

    // Set PWM once (if any phase is active (All PHases share same PWM source check PROTO_V0 hardware reference))
    if (a || b || c) {
        Speed_Channel::duty(effDuty_fixed);
    }
}

