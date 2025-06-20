#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include "Core/core.h"
#include <stdint.h>

 // Functions Prototypes

 

typedef struct GPIO_struct{


    void gpio_Pin_setDirection(uint8_t pin, uint8_t direction);
    void gpio_Pin_write(uint8_t pin, uint8_t value);
    uint8_t gpio_Pin_read(uint8_t pin);
    
} GPIO_t; 

#endif // GPIO_H





//#define DDRB _SFR_IO8(0x04) remember DDRx is a memory address 
