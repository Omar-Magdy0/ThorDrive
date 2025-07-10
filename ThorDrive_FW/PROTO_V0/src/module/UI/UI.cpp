#include "UI.h"


void UI::Init(){
    PeriphInit();
}

void UI::Update(uint32_t t_ms)
{
    Ctrl_Button.update(t_ms);
    Ctrl_Led.update(t_ms);
}
