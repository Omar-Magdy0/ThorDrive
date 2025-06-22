/*
 * BLCD_FW.cpp
 *
 * Created: 6/21/2025 11:46:07 AM
 * Author : 20114
 */ 

#include "Config.h"
#include <math.h>
#include <string.h>

#include "core/softTimer.h"
#include "module/controller.h"
#include "hal/hal.h"
#include "core/sys.h"

controller_t controller;

int main(void)
{
    char debug_msg[80];

    hal_init(); // Initialize hardware abstraction layer
    sys_init();

    //non deterministic timing task
    simpleTimer t1000;

    
    sprintf(debug_msg, "BLDC Motor Controller Firmware v0.1\n");
    uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));

    sprintf(debug_msg, "**SYS_TICKER**\n");
    uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));

    sprintf(debug_msg, "Actual Tick Frequency %i ; Freq_Error_PPM %lu\n", tickerStat.actualFreq, tickerStat.error_ppm);
    uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));
 
    while (1) 
    {
        t1000.update(TICK_TO_mS(getTicks()));
        //1s interval non deterministic timing task
        if(t1000.checkTask(1000)) 
        {
            float speedPot = 50;  
            sprintf(debug_msg, "**Controller**\nenabled: %d; running = %d", controller.enabled_flag, controller.running_flag);
            uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));

            sprintf(debug_msg, "ticks : %" PRIu32 "\n", getTicks());
            uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));
            
            sprintf(debug_msg, "Time_s : %i\n", TICK_TO_S(getTicks()));
            uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));
            
            sprintf(debug_msg, "speed: %i\ntrap triggers: %" PRIu32 "\n\n\n\n", (uint8_t)controller.getCurrentSpeed(), controller.trap_triggers);
            uartint_transmitBurst((uint8_t *)debug_msg, strlen(debug_msg));

            if(controller.running_flag){
                controller.setTargetSpeed(speedPot); // Set target speed based on some input (e.g., potentiometer)
            }

            if(gpio_PinRead(CTRL_BTN_PinNum) == CTRL_BTN_ON){
                if(controller.running_flag){
                    controller.stop();
                    controller.setTargetSpeed(0);
                }else{
                    controller.start();
                }
            }

        }

        // Update the controller state
        controller.loop(TICK_TO_mS(getTicks()));

    }
}





