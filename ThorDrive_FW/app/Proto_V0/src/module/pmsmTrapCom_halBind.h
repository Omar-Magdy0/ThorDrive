#pragma once
#include "thorHal/hal.h"
#include "pmsmTrapCom.h"
#include "Config.h"
#include <modm/platform.hpp>

DEFINE_PIN(Driver_Ah, DRIVER_Ah_PinNum, DRIVER_Ah_ON);
DEFINE_PIN(Driver_Bh, DRIVER_Bh_PinNum, DRIVER_Bh_ON);
DEFINE_PIN(Driver_Ch, DRIVER_Ch_PinNum, DRIVER_Ch_ON);
DEFINE_PIN(Driver_Al, DRIVER_Al_PinNum, DRIVER_Al_ON);
DEFINE_PIN(Driver_Bl, DRIVER_Bl_PinNum, DRIVER_Bl_ON);
DEFINE_PIN(Driver_Cl, DRIVER_Cl_PinNum, DRIVER_Cl_ON);
DEFINE_PIN(Speed, SPEED_PinNum, SPEED_ON);

DEFINE_PIN(Hall_A, HALL_A_PinNum, HALL_A_ON);
DEFINE_PIN(Hall_B, HALL_B_PinNum, HALL_B_ON);
DEFINE_PIN(Hall_C, HALL_C_PinNum, HALL_C_ON);
using Speed_TimPwm = TimPwm<1>;
using Speed_Channel = Speed_TimPwm::Channel<ChannelName::B>;

using HallGpioSet = modm::platform::SoftwareGpioPort<Hall_A, Hall_B, Hall_C>;

static_assert(HallGpioSet::number_of_ports == 1, "Hall sensors must be in same port On Atmega328p");
