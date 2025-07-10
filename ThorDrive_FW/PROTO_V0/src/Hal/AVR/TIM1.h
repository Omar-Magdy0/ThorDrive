#pragma once
#include <avr/io.h>


void TIM1Pwm_init(uint32_t frequency);
uint16_t TIM1Pwm_max();
/**
 * Set PWM duty cycle on Pin 10 (PB2/OC1B)
 * @param duty 0-100 (percentage) or 0-MAX_PWM_DUTY (raw value)
 * @param is_percent true=duty is percentage, false=raw value
 */
void TIM1Pwm_ScaleToMax(uint16_t* duty_UQ16, uint16_t size);
void TIM1APwm_duty(uint16_t val);
void TIM1BPwm_duty(uint16_t val);
void TIM1APwm_init(bool invert);
void TIM1BPwm_init(bool invert);