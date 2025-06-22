
#pragma once
#include "../core/softTimer.h"
#include "../hal/hal.h"
#include "../Config.h"
#include "HAL_moduleBind.h"

#define FORWARD 1
#define REVERSE 0
#define HALLSENSOR_FEEDBACK 1
#define BEMF_FEEDBACK 0
#define hall_abc(a, b, c)(\
    ((a) << 2) | ((b) << 1) | (c) \
)



//Program State Management Structures
struct hall_t{
    uint8_t getState(){
            //Transform the Hall effect sensor Logic (inverted/non-inverted)  to unified On/Off logic
        uint8_t hallA = gpio_PinRead(HALL_A_PinNum) ^ !HALL_A_ON;
        uint8_t hallB = gpio_PinRead(HALL_B_PinNum) ^ !HALL_B_ON;
        uint8_t hallC = gpio_PinRead(HALL_C_PinNum) ^ !HALL_C_ON;
    // Process the Hall sensor states
        return ((hallA << 2) | (hallB << 1) | hallC); // Combine states into a single byte
    }
    bool connected_flag = true;
    bool badSequence_flag = false;
};




struct controller_t{
    private:
        float current_speed = 0; // 0-100% speed
        float target_speed = 0;
        unsigned long t_ms_lastACC = 0;
    public:

    
    bool feedBack = HALLSENSOR_FEEDBACK; // true = HALL sensor feedback, false = BEMF feedback
    bool enabled_flag = true; // true = enabled, false = disabled
    bool running_flag = false; // true = running, false = stopped
    bool direction = FORWARD; // true = forward, false = reverse
    bool overCurrent_flag = false; // true = overcurrent detected, false = normal operation
    unsigned long trap_triggers = 0;
    simpleTimer ledToggleTimer;
    hall_t hall;

    void gpio_init()
    {
        gpio_SetDirection(HALL_A_PinNum,INPUT_PULLUP);
	    gpio_SetDirection(HALL_B_PinNum,INPUT_PULLUP);
	    gpio_SetDirection(HALL_C_PinNum,INPUT_PULLUP);
        
	    gpio_SetDirection(SPEED_PinNum,OUTPUT);
        
	    gpio_SetDirection(DRIVER_Ah_PinNum,OUTPUT);
	    gpio_SetDirection(DRIVER_Bh_PinNum,OUTPUT);
	    gpio_SetDirection(DRIVER_Ch_PinNum,OUTPUT);
	    gpio_SetDirection(DRIVER_Al_PinNum,OUTPUT);
	    gpio_SetDirection(DRIVER_Bl_PinNum,OUTPUT);
	    gpio_SetDirection(DRIVER_Cl_PinNum,OUTPUT);

        gpio_SetDirection(HALT_LED_PinNum,OUTPUT);
        
        gpio_SetDirection(CTRL_BTN_PinNum,INPUT);

        //Initialize PinStates
        gpio_PinWrite(SPEED_PinNum, !SPEED_ON);

        gpio_PinWrite(DRIVER_Ah_PinNum, DRIVER_Ah_ON);
        gpio_PinWrite(DRIVER_Bh_PinNum, DRIVER_Bh_ON);
        gpio_PinWrite(DRIVER_Ch_PinNum, DRIVER_Ch_ON);
        gpio_PinWrite(DRIVER_Al_PinNum, DRIVER_Al_ON);
        gpio_PinWrite(DRIVER_Bl_PinNum, DRIVER_Bl_ON);
        gpio_PinWrite(DRIVER_Cl_PinNum, DRIVER_Cl_ON);
        
        gpio_PinWrite(HALT_LED_PinNum, !HALT_LED_ON);
    }

    float getCurrentSpeed() const { return current_speed;}
    void setTargetSpeed(float newSpeed) {
        if (newSpeed <= minSpeed_perc) {
            target_speed = minSpeed_perc;
        } else if(newSpeed >= maxSpeed_perc) {
            target_speed = maxSpeed_perc;
        } else {
            target_speed = newSpeed;
        }
    }

    void accellerate(uint32_t t_ms){
        uint32_t dt_ms = t_ms - t_ms_lastACC;
        
        if(fabs(target_speed - current_speed) > (accelleration_pps * dt_ms) / 1000.0f){
            current_speed = target_speed;
        }else{
            if(target_speed < current_speed){
                current_speed -= (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
            }else{
                current_speed += (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
            }
            //setSpeed_duty(current_speed);
            t_ms_lastACC = t_ms;
        }
    }


    void commutateHALL(){
        trap_triggers++;
        if(enabled_flag && running_flag){
            if(direction == FORWARD){
                switch(hall.getState()) {
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
                    enabled_flag = false;
                    stop();
                    break;
                }
            }
            else{
                switch(hall.getState()) {
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
                    enabled_flag = false;
                    stop();
                    break;
                }
            }
        }
    }

    void commutateBEMF(void){
        trap_triggers++;
    }

    void start(){
        if(trap_triggers == 0 && enabled_flag && !running_flag){
            if(feedBack == HALLSENSOR_FEEDBACK){
                commutateHALL();
            }else if(feedBack == BEMF_FEEDBACK){
                commutateBEMF();
            }
        }
        running_flag = true;
    }

    void stop(){
        gpio_PinWrite(DRIVER_Ah_PinNum, !DRIVER_Ah_ON);
        gpio_PinWrite(DRIVER_Bh_PinNum, !DRIVER_Bh_ON);
        gpio_PinWrite(DRIVER_Ch_PinNum, !DRIVER_Ch_ON);
        gpio_PinWrite(DRIVER_Al_PinNum, !DRIVER_Al_ON);
        gpio_PinWrite(DRIVER_Bl_PinNum, !DRIVER_Bl_ON);
        gpio_PinWrite(DRIVER_Cl_PinNum, !DRIVER_Cl_ON);
        trap_triggers = 0;
        running_flag = false;
    }


    void loop(uint32_t t_ms){
        //Accelleration Controller
        accellerate(t_ms);

        // Led Controller for State Feedback
        ledToggleTimer.update(t_ms);
        if(running_flag){
            gpio_PinWrite(HALT_LED_PinNum, HALT_LED_ON);
        }else if(overCurrent_flag){
            if(ledToggleTimer.checkTask(500)) {
                gpio_PinToggle(HALT_LED_PinNum);
            }
        }else if(hall.badSequence_flag){
            if(ledToggleTimer.checkTask(2000)) {
                gpio_PinToggle(HALT_LED_PinNum);
            }
        }else if(!running_flag && !overCurrent_flag && !hall.badSequence_flag){
            gpio_PinWrite(HALT_LED_PinNum, !HALT_LED_ON);
        }


    }
};