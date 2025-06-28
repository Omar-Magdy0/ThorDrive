/*
 * GPIO.cpp
 *
 * Created: 6/10/2025 9:04:07 AM
 * Author : 20114
 */ 

 #include <avr/io.h>
 #include "GPIO.h"


#include <avr/io.h>

// Internal mapping functions
static inline volatile uint8_t* _getPortReg(uint8_t pin) {
    return (pin < 8) ? &PORTD : (pin < 14) ? &PORTB : &PORTC;
}

static inline volatile uint8_t* _getDDRReg(uint8_t pin) {
    return (pin < 8) ? &DDRD : (pin < 14) ? &DDRB : &DDRC;
}

static inline volatile uint8_t* _getPINReg(uint8_t pin) {
    return (pin < 8) ? &PIND : (pin < 14) ? &PINB : &PINC;
}

static inline uint8_t _getBitPos(uint8_t pin) {
    return (pin < 8) ? pin : (pin < 14) ? (pin - 8) : (pin - 14);
}

// Modified functions (same signatures but using pin numbers)
void gpio_SetDirection(uint8_t pin, uint8_t mode) {
    volatile uint8_t *ddr = _getDDRReg(pin);
    uint8_t bit = _getBitPos(pin);
    
    if (mode == OUTPUT) {
        *ddr |= (1 << bit);
    } else if (mode == INPUT) {
        *ddr &= ~(1 << bit);
        volatile uint8_t *port = _getPortReg(pin);
        *port &= ~(1 << bit); // Disable pull-up resistor
    } else if (mode == INPUT_PULLUP) {
        *ddr &= ~(1 << bit); // Set as input
        volatile uint8_t *port = _getPortReg(pin);
        *port |= (1 << bit); // Enable pull-up resistor
    } else {
        // Invalid mode, do nothing or handle error
    }
}

void gpio_PinWrite(uint8_t pin, uint8_t value) {
    volatile uint8_t *port = _getPortReg(pin);
    uint8_t bit = _getBitPos(pin);
    
    if (value == HIGH) {
        *port |= (1 << bit);
    } else {
        *port &= ~(1 << bit);
    }
}

void gpio_PinToggle(uint8_t pin) {
    volatile uint8_t *port = _getPortReg(pin);
    uint8_t bit = _getBitPos(pin);
    *port ^= (1 << bit);
}

uint8_t gpio_PinRead(uint8_t pin) {
    volatile uint8_t *pin_reg = _getPINReg(pin);
    uint8_t bit = _getBitPos(pin);
    return ((*pin_reg >> bit) & 0x01);
}
 

void gpio_Init(void)
{
    //INITALIZE ALL PINS AS INPUT_PULLUP 
    for(int pin = 0; pin < 19; pin++){
        gpio_SetDirection(pin, INPUT_PULLUP); // Set all pins to input with pull-up
    }
}

