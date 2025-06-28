#pragma once

#include "adc.h"
#include "GPIO.h"
#include "TIM0.h"
#include "TIM1.h"
#include "TIM2_sys.h"
#include "PCINT.h"
#include "Config.h"
#include <avr/interrupt.h>
#include <avr/io.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "hal/uartint.h"
#include "hal/adc.h"

#ifdef __cplusplus
}
#endif

static inline void hal_init(void)
{
    gpio_Init();
    adc_init();
    uartint_init(SerialBaud);
    sei();
}