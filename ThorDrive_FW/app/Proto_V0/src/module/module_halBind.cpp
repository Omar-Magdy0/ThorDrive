#include "pmsmTrapCom_halBind.h"
#include <modm/platform.hpp>

inline void pcint_HALL_Handler(){
    pmsmTrapCom.commutateHALL();
}

MODM_ISR(PCINT0){
    pcint_HALL_Handler();
}

MODM_ISR(PCINT1){
    pcint_HALL_Handler();
}

MODM_ISR(PCINT2){
    pcint_HALL_Handler();
}