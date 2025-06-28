#include "sys.h"
#include <math.h>


void systemCtrl_t::init(){
    
}

void systemCtrl_t::accellerate_effDuty(uint32_t t_ms){
    uint32_t dt_ms = t_ms - t_ms_last;
    
    if(fabs(target_effDuty - current_effDuty) > (accelleration_pps * dt_ms) / 1000.0f){
        current_effDuty = target_effDuty;
    }else{
        if(target_effDuty < current_effDuty){
            current_effDuty -= (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
        }else{
            current_effDuty += (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
        }
        t_ms_last = t_ms;
    }
}
