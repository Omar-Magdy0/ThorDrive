

#ifndef INT_H
#define INT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//configurations //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
PCINT0 ? corresponds to PB0 (pin 14)

PCINT1 ? corresponds to PB1 (pin 15)

PCINT3 ? corresponds to PB3 (pin 17)
YOU can change the config through HALL_PINS_MASK
*/

//////////////////////////////////////////////////////////////////////////////////////////////////

void PCINT_enable(uint8_t pin);
void PCINT_disable(uint8_t pin);




#endif


