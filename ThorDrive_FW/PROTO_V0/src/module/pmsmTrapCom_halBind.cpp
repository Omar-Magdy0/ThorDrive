#include "pmsmTrapCom_halBind.h"


hallSensor_value hall_t::read(){
   hallSensor_value hallVal;
   hallVal.hallA = gpio_PinRead(HALL_A_PinNum) ^ HALL_A_INVERT;
   hallVal.hallB = gpio_PinRead(HALL_B_PinNum) ^ HALL_B_INVERT;
   hallVal.hallC = gpio_PinRead(HALL_C_PinNum) ^ HALL_C_INVERT;
   return hallVal;
}

void hall_t::periph_init(){
    gpio_SetDirection(HALL_A_PinNum, INPUT_PULLUP); 
    gpio_SetDirection(HALL_B_PinNum, INPUT_PULLUP); 
    gpio_SetDirection(HALL_C_PinNum, INPUT_PULLUP); 
    PCINT_enable(HALL_A_PinNum);
    PCINT_enable(HALL_B_PinNum);
    PCINT_enable(HALL_C_PinNum);
}

void pmsmTrapCom_t::periph_init(uint32_t swchFreq)
{
    TIM1Pwm_init(swchFreq);
    TIM1APwm_init(SPEED_INVERT);
    effDuty_fixed_Max = TIM1Pwm_max();
    
    gpio_SetDirection(DRIVER_Ah_PinNum, OUTPUT);
    gpio_SetDirection(DRIVER_Bh_PinNum, OUTPUT);
    gpio_SetDirection(DRIVER_Ch_PinNum, OUTPUT);
    gpio_SetDirection(DRIVER_Al_PinNum, OUTPUT);
    gpio_SetDirection(DRIVER_Bl_PinNum, OUTPUT);
    gpio_SetDirection(DRIVER_Cl_PinNum, OUTPUT);

    gpio_PinWrite(DRIVER_Ah_PinNum, LOW^DRIVER_Ah_INVERT);
    gpio_PinWrite(DRIVER_Bh_PinNum, LOW^DRIVER_Bh_INVERT);
    gpio_PinWrite(DRIVER_Ch_PinNum, LOW^DRIVER_Ch_INVERT);
    gpio_PinWrite(DRIVER_Al_PinNum, LOW^DRIVER_Al_INVERT);
    gpio_PinWrite(DRIVER_Bl_PinNum, LOW^DRIVER_Bl_INVERT);
    gpio_PinWrite(DRIVER_Cl_PinNum, LOW^DRIVER_Cl_INVERT);
}

void pmsmTrapCom_t::driverWrite(pwmRes a, pwmRes b, pwmRes c, bool aSide, bool bSide, bool cSide)
{
    // Phase A
    /*pwmRes n  defines duty 0 for floating phase and effDuty_fixed_max as the maximum duty
    nSide determine which side of the half bridge is active
    */    
    gpio_PinWrite(DRIVER_Ah_PinNum, (a && aSide)   ^DRIVER_Ah_INVERT   );
    gpio_PinWrite(DRIVER_Bh_PinNum, (a && !aSide)  ^DRIVER_Bh_INVERT   );
    gpio_PinWrite(DRIVER_Ch_PinNum, (b && bSide)   ^DRIVER_Ch_INVERT   );
    gpio_PinWrite(DRIVER_Al_PinNum, (b && !bSide)  ^DRIVER_Al_INVERT   );
    gpio_PinWrite(DRIVER_Bl_PinNum, (c && cSide)   ^DRIVER_Bl_INVERT   );
    gpio_PinWrite(DRIVER_Cl_PinNum, (c && !cSide)  ^DRIVER_Cl_INVERT   );

    // Set PWM once (if any phase is active (All PHases share same PWM source check PROTO_V0 hardware reference))
    if (a || b || c) {
        TIM1APwm_duty(effDuty_fixed);
    }
}

