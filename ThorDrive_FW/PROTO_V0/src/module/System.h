#pragma once
#include <stdint.h>
#include "Config.h"
#include "pmsmControl/pmsmControl.h"
#include "UI/UI.h"

class System{
  private:
    //utility for controlled acceleration can be disabled
    inline static float current_effDuty;
    inline static float target_effDuty;
    inline static uint32_t t_ms_last;
    inline static bool _accellerate_active = false;
    inline static pmsmControl::IController::State pmsmControllerState;
    inline static pmsmControl::IController::Config trapControllerConfig;
    inline static pmsmControl::IController* pmsmcontroller = pmsmControl::Controller::SetActiveController(pmsmControl::ControllerType::Trapezoidal);

  public:
    static void Init();
    static void Update(uint32_t t_ms);
 
    static float GetCurrentSpeed();
    static void SetTargetSpeed(float newSpeed);

    //Sets effective Duty Immediately
    static void SetEffDuty(float newEffDuy);

    //Sets Target effective Duty (Allows for acceleration)
    static void SetTargetEffDuy(float newEffDuy);
    static void AccellerateEffDuty(uint32_t t_ms);
};