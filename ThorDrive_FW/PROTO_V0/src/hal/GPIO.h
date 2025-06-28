#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h> // for reg names should we do them ourselves ?



// Constants for pin states
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1

// Get PORT register from Arduino pin
#define PIN_TO_PORT(pin) ( \
    (pin) <= 7  ? &PORTD : \
    (pin) <= 13 ? &PORTB : \
    &PORTC )

// Get DDR register from Arduino pin
#define PIN_TO_DDR(pin) ( \
    (pin) <= 7  ? &DDRD : \
    (pin) <= 13 ? &DDRB : \
    &DDRC )

// Get PIN register from Arduino pin
#define PIN_TO_PIN_REG(pin) ( \
    (pin) <= 7  ? &PIND : \
    (pin) <= 13 ? &PINB : \
    &PINC )

// Get bitmask from Arduino pin (e.g., PD2 → 0x04)
#define PIN_TO_BITMASK(pin) ( \
    (pin) <= 7  ? (1 << (pin)) : \
    (pin) <= 13 ? (1 << ((pin) - 8)) : \
    (1 << ((pin) - 14)) )


// Check if pin has PCINT (returns -1 if not available)
#define PIN_TO_PCINT(pin) ( \
    (pin) == 0  ? PCINT16 : \
    (pin) == 1  ? PCINT17 : \
    (pin) == 2  ? PCINT18 : \
    (pin) == 3  ? PCINT19 : \
    (pin) == 4  ? PCINT20 : \
    (pin) == 5  ? PCINT21 : \
    (pin) == 6  ? PCINT22 : \
    (pin) == 7  ? PCINT23 : \
    (pin) == 8  ? PCINT0 : \
    (pin) == 9  ? PCINT1 : \
    (pin) == 10 ? PCINT2 : \
    (pin) == 11 ? PCINT3 : \
    (pin) == 12 ? PCINT4 : \
    (pin) == 13 ? PCINT5 : \
    -1 )

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

 // Functions Prototypes
void gpio_Init(void);
void gpio_SetDirection(uint8_t pin, uint8_t direction);
void gpio_PinWrite(uint8_t pin, uint8_t value);
void gpio_PinToggle(uint8_t pin);
uint8_t gpio_PinRead(uint8_t pin);

#endif // GPIO_H





//#define DDRB _SFR_IO8(0x04) remember DDRx is a memory address 
