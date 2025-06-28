#pragma once
#include <stdint.h>

struct UI{

    private:
    void periph_init();
    void ctrlLED_write(uint8_t logic);
    bool ctrlButt_read();
    
    public:
    void init();
    void update();
    void attachShortClick_Callback(void (*callBack));
    void attachLongClick_Callback(void (*callBack));
    void attachDoubleClick_Callback(void (*callBack));
};