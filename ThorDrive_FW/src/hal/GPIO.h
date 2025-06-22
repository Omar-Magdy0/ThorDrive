#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h> // for reg names should we do them ourselves ?



// Constants for pin states
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1



 // Functions Prototypes
void gpio_Init(void);
void gpio_SetDirection(uint8_t pin, uint8_t direction);
void gpio_PinWrite(uint8_t pin, uint8_t value);
void gpio_PinToggle(uint8_t pin);
uint8_t gpio_PinRead(uint8_t pin);

#endif // GPIO_H





//#define DDRB _SFR_IO8(0x04) remember DDRx is a memory address 
