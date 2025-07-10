#pragma once

#include <avr/io.h> // for reg names should we do them ourselves ?


// Constants for pin states
#define LOW 0
#define HIGH 1

// Get PORT register from Arduino pin
#define PIN_TO_PORT(pin) ( \
    (pin) <= 7  ? PORTD : \
    (pin) <= 13 ? PORTB : \
    PORTC )

// Get DDR register from Arduino pin
#define PIN_TO_DDR(pin) ( \
    (pin) <= 7  ? DDRD : \
    (pin) <= 13 ? DDRB : \
    DDRC )

// Get PIN register from Arduino pin
#define PIN_TO_PIN_REG(pin) ( \
    (pin) <= 7  ? PIND : \
    (pin) <= 13 ? PINB : \
    PINC )

// Get the correct PCMSK register for a given Arduino pin
#define PIN_TO_PCMSK(pin) ( \
    (pin) <= 7  ? PCMSK2 : \
    (pin) <= 13 ? PCMSK0 : \
    PCMSK1 )

// Get the correct PCIE bit in PCICR for a given Arduino pin
#define PIN_TO_PCIE(pin) ( \
    (pin) <= 7  ? PCIE2 : \
    (pin) <= 13 ? PCIE0 : \
    PCIE1 )

// Get PCINT number (0-23) for a given Arduino pin
#define PIN_TO_PCINT(pin) ( \
    (pin) <= 7  ? (PCINT16 + (pin)) : \
    (pin) <= 13 ? (PCINT0 + ((pin) - 8)) : \
    (PCINT8 + ((pin) - 14)) )

// Get bitmask from Arduino pin (e.g., PD2 → 0x04)
#define PIN_TO_BITMASK(pin) ( \
    (pin) <= 7  ? (1 << (pin)) : \
    (pin) <= 13 ? (1 << ((pin) - 8)) : \
    (pin) <= 19 ?(1 << ((pin) - 14)) : \
    -1)

#define PIN_TO_PORTIDX(pin) ( \
    (pin) <= 7  ? (pin) : \
    (pin) <= 13 ? (pin - 8): \
    (pin) <= 19 ?(pin - 14) : \
    -1)

// Check if pin has EXTINT (returns INT number or -1)
#define PIN_TO_EXTINT(pin) ( \
    (pin) == 2 ? 0 : \
    (pin) == 3 ? 1 : \
    -1 )

// Check if a pin has EXTINT (returns true/false)
#define PIN_HAS_EXTINT(pin) (PIN_TO_EXTINT(pin) != -1)

// Check if a pin has PCINT (returns true/false)
#define PIN_HAS_PCINT(pin) (PIN_TO_PCINT(pin) != -1)


// Check if pin has PWM (returns true/false)
#define PIN_HAS_PWM(pin) ( \
    (pin) == 3  || \
    (pin) == 5  || \
    (pin) == 6  || \
    (pin) == 9  || \
    (pin) == 10 || \
    (pin) == 11 )

// Check if pin has ADC (returns ADC channel or -1)
#define PIN_TO_ADC(pin) ( \
    (pin) == A0 ? 0 : \
    (pin) == A1 ? 1 : \
    (pin) == A2 ? 2 : \
    (pin) == A3 ? 3 : \
    (pin) == A4 ? 4 : \
    (pin) == A5 ? 5 : \
    -1 )

// Check if a pin has ADC (returns true/false)
#define PIN_HAS_ADC(pin) (PIN_TO_ADC(pin) != -1)

#define _PCINT_vect0_ 0
#define _PCINT_vect1_ 1
#define _PCINT_vect2_ 2

#define PIN_TO_PCINTVectNum(pin)(\
    ((pin) < 8)? _PCINT_vect2_ : \
    ((pin) >= 8 && (pin) < 14)? _PCINT_vect0_: \
    ((pin) >= 14 && (pin) < 20)? _PCINT_vect1_: -1 \
)



#define PINS_SHARE_PCINT_GROUP(pin1, pin2) ( \
    ((pin1) < 8 && (pin2) < 8) || \
    (   ((pin1) >= 8 && (pin1) < 14) && ((pin2) >= 8 && (pin2) < 14)    ) || \
    (   ((pin1) >= 14 && (pin1) < 20) && ((pin2) >= 14 && (pin2) < 20)  ) \
)


namespace Gpio{

enum class InputType{
    Floating,
    PullUp
};

enum class OutputType{
    PushPull
};

enum class ExtIntMode {
    Low = 0,        // 0b00
    Change = 1,     // 0b01
    Falling = 2,    // 0b10
    Rising = 3      // 0b11
};

template <uint8_t Gpio_Num, bool invert = false>
struct Pin{
    private:
    // Compile-time calculated constants
    static constexpr uint8_t MASK = PIN_TO_BITMASK(Gpio_Num);
    static constexpr uint8_t INV_MASK = invert ? MASK : 0;

    // Interrupt-related constants (evaluated at compile-time)
    static constexpr int8_t PCINT_NUM = PIN_TO_PCINT(Gpio_Num);
    static constexpr int8_t EXTINT_NUM = PIN_TO_EXTINT(Gpio_Num);
    static constexpr int8_t PCINT_VECT = PIN_TO_PCINTVectNum(Gpio_Num);

    public:

    static inline void SetInput(InputType inputType) {
        // DDR bit = 0 (input), PORT bit = 1 for pull-up if requested
        PIN_TO_DDR(Gpio_Num) &= ~MASK;
        if (inputType == InputType::PullUp) {
            PIN_TO_PORT(Gpio_Num) |= MASK;
        } else {
            PIN_TO_PORT(Gpio_Num) &= ~MASK;
        }
    }

    static inline void SetOutput(OutputType /*outputType*/) {
        // DDR bit = 1 (output)
        PIN_TO_DDR(Gpio_Num) |= MASK;
    }

    static inline void Write(bool logicLevel) {
        if (logicLevel ^ (INV_MASK != 0)) {
            PIN_TO_PORT(Gpio_Num) |= MASK;   // Set bit
        } else {
            PIN_TO_PORT(Gpio_Num) &= ~MASK;  // Clear bit
        }
    }

    static inline void Toggle() {
        PIN_TO_PORT(Gpio_Num) ^= MASK;  // Writing 1 to PINx toggles PORTx (AVR magic)
    }

    static inline bool Read() {
        return (PIN_TO_PIN_REG(Gpio_Num) & MASK) ^ (INV_MASK != 0);
    }

    // ============== INTERRUPT METHODS ==============
    
    // PCINT Control
    static inline void EnablePCINT() {
        if constexpr (PCINT_NUM != -1) {
            PIN_TO_PCMSK(Gpio_Num) |= (1 << PCINT_VECT);
            PIN_TO_PCMSK(Gpio_Num) |= MASK;
        }
    }
    
    static inline void DisablePCINT() {
        if constexpr (PCINT_NUM != -1) {
            PIN_TO_PCMSK(Gpio_Num) &= ~MASK;
            // Only disable PCICR if no other pins in group are using it
            if ((PIN_TO_PCMSK(Gpio_Num) & ~MASK) == 0) {
                PCICR &= ~(1 << PCINT_VECT);
            }
        }
    }
    
    // EXTINT Control
    static inline void EnableEXTINT(ExtIntMode mode) {
        if constexpr (EXTINT_NUM != -1) {
            constexpr uint8_t shift = EXTINT_NUM * 2;
            EICRA = (EICRA & ~(0b11 << shift)) | (static_cast<uint8_t>(mode) << shift);
            EIMSK |= (1 << EXTINT_NUM);
        }
    }
    
    static inline void DisableEXTINT() {
        if constexpr (EXTINT_NUM != -1) {
            EIMSK &= ~(1 << EXTINT_NUM);
        }
    }
    
    // Utility methods
    static constexpr bool HasPCINT() { return PCINT_NUM != -1; }
    static constexpr bool HasEXTINT() { return EXTINT_NUM != -1; }

};
    
    typedef void(*handler)(void);
    bool AttachPCINT(uint8_t pinNum, handler);
    bool DettachPCINT(uint8_t pinNum);
}

//#define DDRB _SFR_IO8(0x04) remember DDRx is a memory address 
