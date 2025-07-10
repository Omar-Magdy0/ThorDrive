#include "System.h"
#include <math.h>

using namespace pmsmControl;

void System::Init(){
    UI::Init();
    UI::Ctrl_Button.subscribe([](Button::Event e){
        switch (e)
        {
        case Button::Event::SingleClick:
            /* code */
            if(UI::Ctrl_Led.getState() == Led::State::Off){
                pmsmcontroller->Init();
                UI::Ctrl_Led.setState(Led::State::On);
            }else{
                pmsmcontroller->Init();
                UI::Ctrl_Led.setState(Led::State::Off);
            }
            break;
        case Button::Event::DoubleClick:

            break;
        case Button::Event::TripleClick:

            break;
        case Button::Event::LongClick:

            break;
        case Button::Event::ExtraLongClick:
            /* code */
            if(trapControllerConfig.direction == Direction::Forward){
                trapControllerConfig.direction = Direction::Backward;
            }else{
                trapControllerConfig.direction = Direction::Forward;
            }
            pmsmcontroller->SetConfig(trapControllerConfig);
            break;
        default:
            break;
        }
    ;});

    trapControllerConfig.direction = Direction::Forward;
    trapControllerConfig.polePairs = POLE_PAIRS;
    trapControllerConfig.switching_freq = SWITCHING_FREQ;
    trapControllerConfig.effDuty_float = 0.7;
    
    pmsmcontroller->SetConfig(trapControllerConfig);
    pmsmcontroller->Init();
}

void System::SetTargetEffDuy(float newEffDuty)
{
    _accellerate_active = true;
    target_effDuty = newEffDuty;
}

void System::SetEffDuty(float effDuty){
    trapControllerConfig.effDuty_float = effDuty;
    pmsmcontroller->SetConfig(trapControllerConfig);
}

void System::AccellerateEffDuty(uint32_t t_ms)
{
    uint32_t dt_ms = t_ms - t_ms_last;
    
    if(fabs(target_effDuty - current_effDuty) > (accelleration_pps * dt_ms) / 1000.0f){
        current_effDuty = target_effDuty;
        _accellerate_active = false;
    }else{
        if(target_effDuty < current_effDuty){
            current_effDuty -= (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
        }else{
            current_effDuty += (accelleration_pps * dt_ms) / 1000.0f; // Acceleration in percentage per second
        }
        t_ms_last = t_ms;
    }
}

void System::Update(uint32_t t_ms){
    pmsmControllerState = pmsmcontroller->GetState();
    pmsmcontroller->Update(t_ms);
    UI::Update(t_ms);
};

