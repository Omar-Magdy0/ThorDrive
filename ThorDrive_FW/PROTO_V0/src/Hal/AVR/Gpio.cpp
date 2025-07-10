#include <avr/interrupt.h>

#include "Gpio.hpp"


// ATmega328P-specific PCINT capabilities
#define PCINT0_PINS 6  // PB0-PB5 (PB6/PB7 often used for crystal)
#define PCINT1_PINS 7  // PC0-PC6 
#define PCINT2_PINS 8  // PD0-PD7

// Sized dispatcher arrays
volatile Gpio::handler PCINT0_dispatcher[PCINT0_PINS] = {nullptr};
volatile Gpio::handler PCINT1_dispatcher[PCINT1_PINS] = {nullptr};
volatile Gpio::handler PCINT2_dispatcher[PCINT2_PINS] = {nullptr};
// Current enabled PCINT masks
volatile uint8_t PCINT0_enabledmask_ = 0;
volatile uint8_t PCINT1_enabledmask_ = 0;
volatile uint8_t PCINT2_enabledmask_ = 0;


bool Gpio::AttachPCINT(uint8_t pinNum, Gpio::handler cb)
{
    if(!PIN_HAS_PCINT(pinNum)) return false;
    uint8_t PCIE_num = PIN_TO_PCINTVectNum(pinNum);
    uint8_t pinIdx = PIN_TO_PORTIDX(pinNum);
    uint8_t pinMask = PIN_TO_BITMASK(pinNum);
    // Validate pin index
    switch(PCIE_num) {
        case _PCINT_vect0_:
            if(pinIdx >= PCINT0_PINS) return false;
            PCINT0_dispatcher[pinIdx] = cb;
            PCINT0_enabledmask_ |= pinMask;
            break;
            
        case _PCINT_vect1_:
            if(pinIdx >= PCINT1_PINS) return false;
            PCINT1_dispatcher[pinIdx] = cb;
            PCINT1_enabledmask_ |= pinMask;
            break;
            
        case _PCINT_vect2_:
            if(pinIdx >= PCINT2_PINS) return false;
            PCINT2_dispatcher[pinIdx] = cb;
            PCINT2_enabledmask_ |= pinMask;
            break;
            
        default: return false;
    }
    return true;
}

bool Gpio::DettachPCINT(uint8_t pinNum)
{
    if(!PIN_HAS_PCINT(pinNum)) return false;
    
    uint8_t PCIE_num = PIN_TO_PCINTVectNum(pinNum);
    uint8_t pinIdx = PIN_TO_PORTIDX(pinNum);
    uint8_t pinMask = PIN_TO_BITMASK(pinNum);
    
    switch(PCIE_num) {
        case _PCINT_vect0_:
            if(pinIdx >= PCINT0_PINS) return false;
            PCINT0_dispatcher[pinIdx] = nullptr;
            PCINT0_enabledmask_ &= ~pinMask;
            break;
            
        case _PCINT_vect1_:
            if(pinIdx >= PCINT1_PINS) return false;
            PCINT1_dispatcher[pinIdx] = nullptr;
            PCINT1_enabledmask_ &= ~pinMask;
            break;
            
        case _PCINT_vect2_:
            if(pinIdx >= PCINT2_PINS) return false;
            PCINT2_dispatcher[pinIdx] = nullptr;
            PCINT2_enabledmask_ &= ~pinMask;
            break;
            
        default: return false;
    }
    return true;
}

// Optimized dispatcher macros
#define PCINT_DISPATCH_RUN(dispatcher, mask, changed) do { \
    uint8_t active_changes = (changed) & mask; \
    if(active_changes) { \
        uint8_t pin = __builtin_ctz(active_changes); \
        if(dispatcher[pin]) dispatcher[pin](); \
    } \
} while(0)

#define PCINT0_dispatcherRun(changed) PCINT_DISPATCH_RUN(PCINT0_dispatcher, PCINT0_enabledmask_,changed)
#define PCINT1_dispatcherRun(changed) PCINT_DISPATCH_RUN(PCINT1_dispatcher, PCINT1_enabledmask_,changed)
#define PCINT2_dispatcherRun(changed) PCINT_DISPATCH_RUN(PCINT2_dispatcher, PCINT2_enabledmask_,changed)


ISR(PCINT0_vect){
    static uint8_t PORTB_last = PINB;
    uint8_t changed = PORTB_last ^ PINB;
    PORTB_last = PINB;
    PCINT0_dispatcherRun(changed);
}

ISR(PCINT1_vect){
    static uint8_t PORTC_last = PINC;
    uint8_t changed = PORTC_last ^ PINC;
    PORTC_last = PINC;
    PCINT1_dispatcherRun(changed);
}

ISR(PCINT2_vect){
    static uint8_t PORTD_last = PIND;
    uint8_t changed = PORTD_last ^ PIND;
    PORTD_last = PIND;
    PCINT2_dispatcherRun(changed);
}