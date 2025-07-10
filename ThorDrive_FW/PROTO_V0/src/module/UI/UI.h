#pragma once
#include <stdint.h>
#include "UIElement/Button.hpp"
#include "UIElement/Led.hpp"

struct UI{
    private:
    static void PeriphInit();
    static void CtrlLedWrite(bool logic);
    static bool CtrlButtRead();
    
    inline static uint32_t t_ms_last = 0;
    public:
    
    static void Init();
    static void Update(uint32_t t_ms);
    inline static Button Ctrl_Button = Button(CtrlButtRead, Button::Config());
    inline static Led Ctrl_Led = Led(CtrlLedWrite);
};

