#include "pmsmTrapCom.h"
#include <cmath>

 void pmsmTrapCom_t::init(){
    periph_init(SWITCHING_FREQ);
    //hall.periph_init();
 }

void pmsmTrapCom_t::start(){
    if((trap_triggers == 0) && !hardFault_flag && !running_flag){
        if(feedBack_type == HALLSENSOR_FEEDBACK){
            commutateHALL();
        }else if(feedBack_type == BEMF_FEEDBACK){
            commutateBEMF();
        }
    }
    //Dont Count the starting as a trigger , only count the state changes after
    trap_triggers = 0;
    running_flag = true;
}


void pmsmTrapCom_t::stop(){
    //Disable All phases (ie. leave them floating)
    driverWrite(0, 0, 0, LOW, LOW, LOW);
    trap_triggers = 0;
    running_flag = false;
}

void pmsmTrapCom_t::setEffDuty(float _effDuty){
    effDuty_float = _effDuty;
    effDuty_fixed = effDuty_float*effDuty_fixed_Max;
}

void pmsmTrapCom_t::commutateHALL(){
    hallSensor_value _hallread = hall.read();
    bool A = _hallread.hallA;
    bool B = _hallread.hallB;
    bool C = _hallread.hallC;
    uint8_t hallNum = A<<2 | B<<1 | C;
    if(lastHallNum == hallNum)return;
    
    trap_triggers++;
    lastHallNum = hallNum;
    if(!hardFault_flag && running_flag){
        if(direction == FORWARD){
            switch(hallNum) {
            case hall_abc(1, 0, 1):
                break;
            case hall_abc(0, 0, 1):
                break;
            case hall_abc(0, 1, 1):
                break;
            case hall_abc(0, 1, 0):
                break;
            case hall_abc(1, 1, 0):
                break;
            case hall_abc(1, 0, 0):
                break;
            case hall_abc(0, 0, 0):
            case hall_abc(1, 1, 1): 
                hall.connected_flag = false;
                hardFault_flag = true;
                stop();
                break;
            }
        }
        else{
            switch(hallNum) {
            case hall_abc(1, 0, 1):
                break;
            case hall_abc(0, 0, 1):
                break;
            case hall_abc(0, 1, 1):
                break;
            case hall_abc(0, 1, 0):
                break;
            case hall_abc(1, 1, 0):
                break;
            case hall_abc(1, 0, 0):
                break;
            case hall_abc(0, 0, 0):
            case hall_abc(1, 1, 1): 
                hall.connected_flag = false;
                hardFault_flag = true;
                stop();
                break;
           }
        }
    }
}

void pmsmTrapCom_t::commutateBEMF(void){
    trap_triggers++;
}

