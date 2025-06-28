
#pragma once

#include "Config.h"
#include <stdint.h>

#define FORWARD 1
#define REVERSE 0
#define HALLSENSOR_FEEDBACK 1
#define BEMF_FEEDBACK 0
#define hall_abc(a, b, c)(\
    ((a) << 2) | ((b) << 1) | (c) \
)

typedef uint16_t pwmRes;

//Program State Management Structures
struct hallSensor_value{
    bool hallA;
    bool hallB;
    bool hallC;
};

struct hall_t{
    void periph_init();
    hallSensor_value read();
    bool connected_flag = true;
    bool badSequence_flag = false;
};


struct pmsmTrapCom_t{
    private:
        uint32_t t_start_ms = 0;
        float effDuty_float = 0;
        pwmRes effDuty_fixed = 0;
        
        hall_t hall;
        uint8_t lastHallNum = 0;
        uint8_t currentHallState = 0;

        uint32_t trap_triggers = 0;
        int32_t trap_triggersDirectional = 0;
        float rotations = 0;
        uint8_t polePairs = POLE_PAIRS;
    public:

    bool feedBack_type = HALLSENSOR_FEEDBACK; // true = HALL sensor feedback, false = BEMF feedback
    bool hardFault_flag = false; 
    bool running_flag = false; // true = running, false = stopped
    bool startFail_flag = false;
    bool overCurrent_flag = false; // true = overcurrent detected, false = normal operation
    bool direction = FORWARD; // true = forward, false = reverse
    
    pwmRes effDuty_fixed_Max = 0;
    void init();
    void periph_init(uint32_t swchFreq);
    void driverWrite(pwmRes a, pwmRes b, pwmRes c, bool aSide, bool bSide, bool cSide);

    void start();
    void stop();

    void setEffDuty(float _effDuty);
    void commutateHALL();
    void commutateBEMF(void);

    void loop(uint32_t t_ms);
};

inline pmsmTrapCom_t pmsmTrapCom;