#include "pmsmTrapCom_halBind.h"


#ifdef __AVR__
//PCINT MANAGEMENT FOR AVR

static_assert(
    PINS_SHARE_PCINT_GROUP(HALL_A_PinNum, HALL_B_PinNum) && 
    PINS_SHARE_PCINT_GROUP(HALL_A_PinNum, HALL_C_PinNum),
    "HALL sensor pins must share the same pin change interrupt vector"
);

#define HALL_CHANGE_MASK ((1<<PIN_TO_BITMASK(HALL_A_PinNum)) | (1<<PIN_TO_BITMASK(HALL_B_PinNum)) | (1<<PIN_TO_BITMASK(HALL_C_PinNum)))
#define HALL_CHANGE_FUNCTION pmsmTrapCom.commutateHALL()

ISR(PCINT0_vect){
    static uint8_t last_val = PORTB;
    uint8_t changed = last_val ^ PORTB;
    #ifdef PIN_TO_PCINTVectNum(HALL_A_PinNum) == _PCINT_vect0_
        //HALL sensor uses PCINT0 pin group
        if(changed & HALL_CHANGE_MASK){
            HALL_CHANGE_FUNCTION;
        }
    #endif    
}

ISR(PCINT1_vect){
    static uint8_t last_val = PORTC;
    uint8_t changed = last_val ^ PORTC;
    #if PIN_TO_PCINTVectNum(HALL_A_PinNum) == _PCINT_vect1_ 
        if(changed & HALL_CHANGE_MASK ){
             HALL_CHANGE_FUNCTION;
        }
        //HALL sensor uses PCINT1 pin group
    #endif   
}

ISR(PCINT2_vect){
    static uint8_t last_val = PORTD;
    uint8_t changed = last_val ^ PORTD;
    #if PIN_TO_PCINTVectNum(HALL_A_PinNum) == _PCINT_vect1_
        if(changed & HALL_CHANGE_MASK ){
              HALL_CHANGE_FUNCTION;
        }
        //HALL sensor uses PCINT2 pin group                     
    #endif   
}

#endif