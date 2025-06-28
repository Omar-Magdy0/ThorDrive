#pragma once
#include <stdint.h>
#include "Config.h"

class systemCtrl_t{
  private:
    //utility for controlled acceleration can be disabled
    float current_effDuty;
    float target_effDuty;

    uint32_t t_ms_last;

  public:
    void init();
    
    float getCurrentSpeed() const;
    void setTargetSpeed(float newSpeed);

    void setEffDuty(float newEffDuy);
    void setTargetEffDuy(float newEffDuy);
    void accellerate_effDuty(uint32_t t_ms);
    void loop(uint32_t t_ms);
};