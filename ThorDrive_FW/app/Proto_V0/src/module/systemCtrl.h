#pragma once
#include <cstdint>
#include "Config.h"

class systemCtrl_t{
  private:
    float current_effDuty;
    float target_effDuty;

    uint32_t t_ms_last;

  public:
    void init();
    void periph_init();
    void ctrlLED_write(uint8_t logic);
    bool ctrlButt_read();
    
    float getCurrentSpeed() const;
    void setTargetSpeed(float newSpeed);


    void setEffDuty(float newEffDuy);
    void accellerate_effDuty(uint32_t t_ms);
    void loop(uint32_t t_ms);
};