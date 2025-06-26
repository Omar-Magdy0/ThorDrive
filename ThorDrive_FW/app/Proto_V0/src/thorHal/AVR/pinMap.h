// pin_map.h
#pragma once
#include <modm/platform.hpp>

namespace PinMapping {
    // Convert Arduino pin numbers (D0-D13) to MODM Gpio types
    template<int PinNum>
    struct MapPin;

    // ATmega328P Arduino Pin Mapping (D0-D13)
    template<> struct MapPin<0>  { using Type = modm::platform::GpioD0; };
    template<> struct MapPin<1>  { using Type = modm::platform::GpioD1; };
    template<> struct MapPin<2>  { using Type = modm::platform::GpioD2; };
    template<> struct MapPin<3>  { using Type = modm::platform::GpioD3; };
    template<> struct MapPin<4>  { using Type = modm::platform::GpioD4; };
    template<> struct MapPin<5>  { using Type = modm::platform::GpioD5; };
    template<> struct MapPin<6>  { using Type = modm::platform::GpioD6; };
    template<> struct MapPin<7>  { using Type = modm::platform::GpioD7; };
    template<> struct MapPin<8>  { using Type = modm::platform::GpioB0; };  // PB0 (D8)
    template<> struct MapPin<9>  { using Type = modm::platform::GpioB1; };  // PB1 (D9)
    template<> struct MapPin<10> { using Type = modm::platform::GpioB2; };  // PB2 (D10)
    template<> struct MapPin<11> { using Type = modm::platform::GpioB3; };  // PB3 (D11)
    template<> struct MapPin<12> { using Type = modm::platform::GpioB4; };  // PB4 (D12)
    template<> struct MapPin<13> { using Type = modm::platform::GpioB5; };  // PB5 (D13)
    template<> struct MapPin<14>  { using Type = modm::platform::GpioC0; };  // PB0 (D8)
    template<> struct MapPin<15>  { using Type = modm::platform::GpioC1; };  // PB1 (D9)
    template<> struct MapPin<16> { using Type = modm::platform::GpioC2; };  // PB2 (D10)
    template<> struct MapPin<17> { using Type = modm::platform::GpioC3; };  // PB3 (D11)
    template<> struct MapPin<18> { using Type = modm::platform::GpioC4; };  // PB4 (D12)
    template<> struct MapPin<19> { using Type = modm::platform::GpioC5; };  // PB5 (D13)

    template <int PinNum, bool Inverted>
    struct PinWrapper {
        using Type = std::conditional_t<
            Inverted,
            modm::platform::GpioInverted<typename MapPin<PinNum>::Type>,
            typename MapPin<PinNum>::Type
        >;
    };
}

    // Correct macro definition
#define DEFINE_PIN(name, num, logicOn) \
    using name = typename PinMapping::PinWrapper<num, !logicOn>::Type