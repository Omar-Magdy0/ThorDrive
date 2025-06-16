/*
 * GPIO.cpp
 *
 * Created: 6/10/2025 9:04:07 AM
 * Author : 20114
 */ 

 #include "GPIO.h"
// Helper macros
#define _GET_PORT(pin) ((pin) < 8 ? &PORTB : ((pin) < 14 ? &PORTC : &PORTD))
#define _GET_DDR(pin)  ((pin) < 8 ? &DDRB  : ((pin) < 14 ? &DDRC  : &DDRD))
#define _GET_PIN(pin)  ((pin) < 8 ? &PINB  : ((pin) < 14 ? &PINC  : &PIND))
#define _GET_BIT(pin)  ((pin) < 8 ? (pin) : ((pin) < 14 ? (pin)-8 : (pin)-14))
#define _GET_MASK(pin) (1 << _GET_BIT(pin))

 void GPIO_t::gpio_Pin_setDirection(uint8_t pin, uint8_t direction) 
 {
    if(direction == OUTPUT)
    {
        SBI(*_GET_DDR(pin), _GET_BIT(pin));
    }
    else if(direction == INPUT)
    {
        CBI(*_GET_DDR(pin), _GET_BIT(pin));
        CBI(*_GET_PORT(pin), _GET_BIT(pin)); // Ensure pin is low if set to input
    }
    else if(direction == INPUT_PULLUP)
    {
        CBI(*_GET_DDR(pin), _GET_BIT(pin)); // Set pin as input
        SBI(*_GET_PORT(pin), _GET_BIT(pin)); // Enable pull-up resistor
    }
 }
 
 void GPIO_t::gpio_Pin_write(uint8_t pin, uint8_t value)
  {
    if (value == HIGH) 
    {
        SBI(*_GET_PORT(pin), _GET_BIT(pin));
    } 
     else if(value == LOW)
    {
        CBI(*_GET_PORT(pin), _GET_BIT(pin)); 
    }
    else if(value == TOGGLE)
    {
        TBI(*_GET_PORT(pin), _GET_BIT(pin));
    }
 }
 
 uint8_t GPIO_t::gpio_Pin_read(uint8_t pin) 
 {
     return (TEST(*_GET_PIN(pin), _GET_BIT(pin)) ? HIGH : LOW);
 }