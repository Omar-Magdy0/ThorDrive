#ifndef TIMER2_PWM_H
#define TIMER2_PWM_H

#include <avr/io.h>
#include "GPIO.h"

extern GPIO_t GPIO1;
// Prescaler options (you can add more if needed)
#define TIMER2_NO_PRESCALER   1
#define TIMER2_PRESCALER_8    2
#define TIMER2_PRESCALER_32   3
#define TIMER2_PRESCALER_64   4
#define TIMER2_PRESCALER_128  5
#define TIMER2_PRESCALER_256  6
#define TIMER2_PRESCALER_1024 7

// PWM Channel Options
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1

//
#define OC2A_PIN 3  // PB3
#define OC2B_PIN 3  // PD3

// Function Prototypes

typedef struct PWM_struct{

// Initialize Timer2 for Fast PWM mode (on OC2A or OC2B)
void timer2PWM_Init(uint8_t channel, uint8_t prescaler);

// Set duty cycle (0–255) on a selected channel
void timer2SetDutyCycle(uint8_t channel, uint8_t duty);

// Optional: Stop PWM
void timer2Stop(void);

}PWM;


#endif // TIMER2_PWM_H
