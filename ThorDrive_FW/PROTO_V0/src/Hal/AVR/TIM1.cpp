#include "TIM1.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

#define TIMER1_TOP(freq) ((F_CPU / (2UL * 1UL * freq)) - 1)

void TIM1Pwm_init(uint32_t frequency) {
    // Configure Timer1 for 10kHz Phase Correct PWM + Interrupt
    TCCR1A = 0;  // Clear register
    TCCR1B = 0;  // Clear register
    
    // Phase Correct PWM Mode (TOP = ICR1, 10-bit)
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13);
    
    // Clock Select: No prescaling (16MHz)
    TCCR1B |= (1 << CS10);
    
    // Set PWM frequency (Phase Correct: f = f_CPU / (2 * N * TOP))
    ICR1 = TIMER1_TOP(frequency);
    
}

uint16_t TIM1Pwm_max(){
    return ICR1;
}

void TIM1BPwm_duty(uint16_t val) {
    OCR1B = val;
}

void TIM1BPwm_init(bool invert) {
    if(invert) {
        // Inverting mode (Clear on match, set at BOTTOM)
        TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
    } else {
        // Non-inverting mode (Set on match, clear at BOTTOM)
        TCCR1A |= (1 << COM1B1);
    }
    OCR1A = 0;
    OCR1B = 0; // Initialize duty cycle to 0
}

void TIM1Pwm_ScaleToMax(uint16_t* duty_UQ16, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        duty_UQ16[i] = uint32_t(duty_UQ16[i] * ICR1) >> 16;
    }
};

void TIM1APwm_duty(uint16_t val){
    OCR1A = val;
}

void TIM1APwm_init(bool invert) {
    if(invert) {
        // Inverting mode (Clear on match, set at BOTTOM)
        TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    } else {
        // Non-inverting mode (Set on match, clear at BOTTOM)
        TCCR1A |= (1 << COM1A1);
    }
    OCR1A = 0;
    OCR1B = 0; // Initialize duty cycle to 0
}

