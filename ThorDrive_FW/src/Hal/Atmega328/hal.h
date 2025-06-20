#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include "GPIO.h"
#include "PWM.h"

struct hal_t{
    gpio_t gpio;
    pwmt_t pwm;
};

#endif // HAL_H