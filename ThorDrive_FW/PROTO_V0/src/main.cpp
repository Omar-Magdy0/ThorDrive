/*
 * BLCD_FW.cpp
 *
 * Created: 6/21/2025 11:46:07 AM
 * Author : 20114
 */ 

#include "Config.h"
#include "module/System.h"
#include "core/softTimer.h"
#include "core/sys.h"
#include "util/delay.h"
#include "hal/hal.h"

#include <string.h>



int main(void)
{
    uartint_init(115200);
    sysTIM_init();
    System::Init();

    uint32_t t_ms = TICK_TO_mS(getTicks());
    UI::Ctrl_Led.setState(Led::State::On);
    char buffer[50];

    
    simpleTimer occ0;
    occ0.update(t_ms);

    simpleTimer occ1;
    occ1.update(t_ms);
    
    while (1) 
    {   
        t_ms = TICK_TO_mS(getTicks());
        occ0.update(t_ms);
        occ1.update(t_ms);

        if(occ0.checkTask(1000)){


        }

        if(occ1.checkTask(50)){
            System::Update(t_ms);
        }
    }
}





