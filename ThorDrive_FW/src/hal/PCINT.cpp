#include "PCINT.h"


// PCINT Register Mapping Macros
#define _PCINT_GET_PCMSK_REG(pin) ((pin) < 8 ? &PCMSK2 : (pin) < 14 ? &PCMSK0 : &PCMSK1)
#define _PCINT_GET_PCIE_BIT(pin)  ((pin) < 8 ? PCIE2 : (pin) < 14 ? PCIE0 : PCIE1)
#define _PCINT_GET_PCINT_BIT(pin) ((pin) < 8 ? (pin) + 16 : (pin) < 14 ? (pin) - 8 : (pin) - 14 + 8)

void PCINT_enable(uint8_t pin) {
    // Validate pin number (0-19 for ATmega328P Arduino pins)
    if (pin > 19) return;
    
    // Enable the pin change interrupt for the specific pin
    *_PCINT_GET_PCMSK_REG(pin) |= (1 << _PCINT_GET_PCINT_BIT(pin));
    
    // Enable the port-level interrupt
    PCICR |= (1 << _PCINT_GET_PCIE_BIT(pin));
}

void PCINT_disable(uint8_t pin) {
    // Validate pin number
    if (pin > 19) return;
    
    // Disable the specific pin interrupt
    volatile uint8_t* pcmsk = _PCINT_GET_PCMSK_REG(pin);
    *pcmsk &= ~(1 << _PCINT_GET_PCINT_BIT(pin));
    
    // Check if we should disable the entire port interrupt
    if (*pcmsk == 0) {
        PCICR &= ~(1 << _PCINT_GET_PCIE_BIT(pin));
    }
}


ISR(PCINT0_vect){
    //Pin change interrupt handle for Hall Sensors
    // Read the state of the Hall sensors and take appropriate action
    
}

//////////////////////////////////////////////