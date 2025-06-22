#pragma once
#include <avr/io.h>


void TIM1Pwm_init(uint32_t frequency);
/**
 * Set PWM duty cycle on Pin 10 (PB2/OC1B)
 * @param duty 0-100 (percentage) or 0-MAX_PWM_DUTY (raw value)
 * @param is_percent true=duty is percentage, false=raw value
 */
void TIM1BPwm_duty(float duty_percent);
void TIM1APwm_duty(float duty_percent);
void TIM1APwm_init(bool no_invert);
void TIM1BPWM_init(bool no_invert);
