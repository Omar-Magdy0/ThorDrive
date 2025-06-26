/*
 * Copyright (c) 2021, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "base.hpp"

/// @cond
namespace modm::platform::detail
{

template<class Signal, Peripheral p> struct SignalConnection;

struct DataUnused {};

struct DataB0 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 0;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT0); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT0); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Clk0 { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Clk0; };
	struct Icp { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Icp; };
};
template<Peripheral p> struct SignalConnection<DataB0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB0::Clk0, p> {
	static_assert((p == Peripheral::Core),"GpioB0::Clk0 only connects to Core!"); };
template<Peripheral p> struct SignalConnection<DataB0::Icp, p> {
	static_assert((p == Peripheral::Tc1),"GpioB0::Icp only connects to Tc1!"); };

struct DataB1 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 1;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT1); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT1); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB1; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Oca { using Data = DataB1; static constexpr Gpio::Signal Signal = Gpio::Signal::Oca; };
};
template<Peripheral p> struct SignalConnection<DataB1::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB1::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB1::Oca, p> {
	static_assert((p == Peripheral::Tc1),"GpioB1::Oca only connects to Tc1!"); };

struct DataB2 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 2;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT2); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT2); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB2; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ocb { using Data = DataB2; static constexpr Gpio::Signal Signal = Gpio::Signal::Ocb; };
	struct Ss { using Data = DataB2; static constexpr Gpio::Signal Signal = Gpio::Signal::Ss; };
};
template<Peripheral p> struct SignalConnection<DataB2::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB2::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB2::Ocb, p> {
	static_assert((p == Peripheral::Tc1),"GpioB2::Ocb only connects to Tc1!"); };
template<Peripheral p> struct SignalConnection<DataB2::Ss, p> {
	static_assert((p == Peripheral::Spi),"GpioB2::Ss only connects to Spi!"); };

struct DataB3 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 3;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT3); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT3); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Mosi { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Mosi; };
	struct Oca { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Oca; };
};
template<Peripheral p> struct SignalConnection<DataB3::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB3::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB3::Mosi, p> {
	static_assert((p == Peripheral::Spi),"GpioB3::Mosi only connects to Spi!"); };
template<Peripheral p> struct SignalConnection<DataB3::Oca, p> {
	static_assert((p == Peripheral::Tc2),"GpioB3::Oca only connects to Tc2!"); };

struct DataB4 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 4;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT4); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT4); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Miso { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Miso; };
};
template<Peripheral p> struct SignalConnection<DataB4::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB4::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB4::Miso, p> {
	static_assert((p == Peripheral::Spi),"GpioB4::Miso only connects to Spi!"); };

struct DataB5 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 5;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT5); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT5); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Sck { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Sck; };
};
template<Peripheral p> struct SignalConnection<DataB5::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB5::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB5::Sck, p> {
	static_assert((p == Peripheral::Spi),"GpioB5::Sck only connects to Spi!"); };

struct DataB6 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 6;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT6); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT6); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Tosc1 { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Tosc1; };
	struct Xtal1 { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Xtal1; };
};
template<Peripheral p> struct SignalConnection<DataB6::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB6::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB6::Tosc1, p> {
	static_assert((p == Peripheral::Tc2),"GpioB6::Tosc1 only connects to Tc2!"); };
template<Peripheral p> struct SignalConnection<DataB6::Xtal1, p> {
	static_assert((p == Peripheral::Core),"GpioB6::Xtal1 only connects to Core!"); };

struct DataB7 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 7;

	inline static void enablePcInterrupt() { PCMSK0 |= (1 << PCINT7); PCICR |= (1 << PCIE0); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK0 & ~(1 << PCINT7); PCMSK0 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE0);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF0)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF0); }
	struct BitBang { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Tosc2 { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Tosc2; };
	struct Xtal2 { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Xtal2; };
};
template<Peripheral p> struct SignalConnection<DataB7::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB7::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB7::Tosc2, p> {
	static_assert((p == Peripheral::Tc2),"GpioB7::Tosc2 only connects to Tc2!"); };
template<Peripheral p> struct SignalConnection<DataB7::Xtal2, p> {
	static_assert((p == Peripheral::Core),"GpioB7::Xtal2 only connects to Core!"); };

struct DataC0 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 0;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT8); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT8); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In0 { using Data = DataC0; static constexpr Gpio::Signal Signal = Gpio::Signal::In0; };
};
template<Peripheral p> struct SignalConnection<DataC0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC0::In0, p> {
	static_assert((p == Peripheral::Adc),"GpioC0::In0 only connects to Adc!"); };

struct DataC1 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 1;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT9); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT9); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC1; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In1 { using Data = DataC1; static constexpr Gpio::Signal Signal = Gpio::Signal::In1; };
};
template<Peripheral p> struct SignalConnection<DataC1::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC1::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC1::In1, p> {
	static_assert((p == Peripheral::Adc),"GpioC1::In1 only connects to Adc!"); };

struct DataC2 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 2;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT10); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT10); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC2; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In2 { using Data = DataC2; static constexpr Gpio::Signal Signal = Gpio::Signal::In2; };
};
template<Peripheral p> struct SignalConnection<DataC2::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC2::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC2::In2, p> {
	static_assert((p == Peripheral::Adc),"GpioC2::In2 only connects to Adc!"); };

struct DataC3 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 3;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT11); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT11); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC3; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In3 { using Data = DataC3; static constexpr Gpio::Signal Signal = Gpio::Signal::In3; };
};
template<Peripheral p> struct SignalConnection<DataC3::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC3::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC3::In3, p> {
	static_assert((p == Peripheral::Adc),"GpioC3::In3 only connects to Adc!"); };

struct DataC4 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 4;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT12); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT12); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC4; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In4 { using Data = DataC4; static constexpr Gpio::Signal Signal = Gpio::Signal::In4; };
	struct Sda { using Data = DataC4; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
};
template<Peripheral p> struct SignalConnection<DataC4::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC4::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC4::In4, p> {
	static_assert((p == Peripheral::Adc),"GpioC4::In4 only connects to Adc!"); };
template<Peripheral p> struct SignalConnection<DataC4::Sda, p> {
	static_assert((p == Peripheral::Twi),"GpioC4::Sda only connects to Twi!"); };

struct DataC5 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 5;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT13); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT13); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC5; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct In5 { using Data = DataC5; static constexpr Gpio::Signal Signal = Gpio::Signal::In5; };
	struct Scl { using Data = DataC5; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
};
template<Peripheral p> struct SignalConnection<DataC5::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC5::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataC5::In5, p> {
	static_assert((p == Peripheral::Adc),"GpioC5::In5 only connects to Adc!"); };
template<Peripheral p> struct SignalConnection<DataC5::Scl, p> {
	static_assert((p == Peripheral::Twi),"GpioC5::Scl only connects to Twi!"); };

struct DataC6 {
	static constexpr Gpio::Port port = Gpio::Port::C;
	static constexpr uint8_t pin = 6;

	inline static void enablePcInterrupt() { PCMSK1 |= (1 << PCINT14); PCICR |= (1 << PCIE1); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK1 & ~(1 << PCINT14); PCMSK1 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE1);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF1)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF1); }
	struct BitBang { using Data = DataC6; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
};
template<Peripheral p> struct SignalConnection<DataC6::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioC6::BitBang only connects to software drivers!"); };

struct DataD0 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 0;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT16); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT16); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Rxd { using Data = DataD0; static constexpr Gpio::Signal Signal = Gpio::Signal::Rxd; };
};
template<Peripheral p> struct SignalConnection<DataD0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD0::Rxd, p> {
	static_assert((p == Peripheral::Usart0),"GpioD0::Rxd only connects to Usart0!"); };

struct DataD1 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 1;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT17); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT17); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD1; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Txd { using Data = DataD1; static constexpr Gpio::Signal Signal = Gpio::Signal::Txd; };
};
template<Peripheral p> struct SignalConnection<DataD1::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD1::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD1::Txd, p> {
	static_assert((p == Peripheral::Usart0),"GpioD1::Txd only connects to Usart0!"); };

struct DataD2 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 2;

	inline static void setInputTrigger(Gpio::InputTrigger trigger) {
		EICRA = (EICRA & ~(0b11 << 2*0)) | (uint8_t(trigger) << 2*0);
	}
	inline static void enableExternalInterrupt() { EIMSK |= (1 << INT0); }
	inline static void disableExternalInterrupt() { EIMSK &= ~(1 << INT0); }
	inline static bool getExternalInterruptFlag() { return (EIFR & (1 << INTF0)); }
	inline static void acknowledgeExternalInterruptFlag() { EIFR |= (1 << INTF0); }
	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT18); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT18); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD2; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
};
template<Peripheral p> struct SignalConnection<DataD2::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD2::BitBang only connects to software drivers!"); };

struct DataD3 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 3;

	inline static void setInputTrigger(Gpio::InputTrigger trigger) {
		EICRA = (EICRA & ~(0b11 << 2*1)) | (uint8_t(trigger) << 2*1);
	}
	inline static void enableExternalInterrupt() { EIMSK |= (1 << INT1); }
	inline static void disableExternalInterrupt() { EIMSK &= ~(1 << INT1); }
	inline static bool getExternalInterruptFlag() { return (EIFR & (1 << INTF1)); }
	inline static void acknowledgeExternalInterruptFlag() { EIFR |= (1 << INTF1); }
	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT19); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT19); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD3; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ocb { using Data = DataD3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ocb; };
};
template<Peripheral p> struct SignalConnection<DataD3::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD3::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD3::Ocb, p> {
	static_assert((p == Peripheral::Tc2),"GpioD3::Ocb only connects to Tc2!"); };

struct DataD4 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 4;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT20); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT20); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD4; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct T { using Data = DataD4; static constexpr Gpio::Signal Signal = Gpio::Signal::T; };
	struct Xck { using Data = DataD4; static constexpr Gpio::Signal Signal = Gpio::Signal::Xck; };
};
template<Peripheral p> struct SignalConnection<DataD4::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD4::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD4::T, p> {
	static_assert((p == Peripheral::Tc0),"GpioD4::T only connects to Tc0!"); };
template<Peripheral p> struct SignalConnection<DataD4::Xck, p> {
	static_assert((p == Peripheral::Usart0),"GpioD4::Xck only connects to Usart0!"); };

struct DataD5 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 5;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT21); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT21); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD5; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ocb { using Data = DataD5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ocb; };
	struct T { using Data = DataD5; static constexpr Gpio::Signal Signal = Gpio::Signal::T; };
};
template<Peripheral p> struct SignalConnection<DataD5::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD5::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD5::Ocb, p> {
	static_assert((p == Peripheral::Tc0),"GpioD5::Ocb only connects to Tc0!"); };
template<Peripheral p> struct SignalConnection<DataD5::T, p> {
	static_assert((p == Peripheral::Tc1),"GpioD5::T only connects to Tc1!"); };

struct DataD6 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 6;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT22); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT22); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD6; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ain0 { using Data = DataD6; static constexpr Gpio::Signal Signal = Gpio::Signal::Ain0; };
	struct Oca { using Data = DataD6; static constexpr Gpio::Signal Signal = Gpio::Signal::Oca; };
};
template<Peripheral p> struct SignalConnection<DataD6::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD6::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD6::Ain0, p> {
	static_assert((p == Peripheral::Ac),"GpioD6::Ain0 only connects to Ac!"); };
template<Peripheral p> struct SignalConnection<DataD6::Oca, p> {
	static_assert((p == Peripheral::Tc0),"GpioD6::Oca only connects to Tc0!"); };

struct DataD7 {
	static constexpr Gpio::Port port = Gpio::Port::D;
	static constexpr uint8_t pin = 7;

	inline static void enablePcInterrupt() { PCMSK2 |= (1 << PCINT23); PCICR |= (1 << PCIE2); }
	inline static void disablePcInterrupt() {
		uint8_t pcmsk = PCMSK2 & ~(1 << PCINT23); PCMSK2 = pcmsk;
		if (pcmsk == 0) PCICR &= ~(1 << PCIE2);
	}
	inline static bool getPcInterruptFlag() { return (PCIFR & (1 << PCIF2)); }
	inline static void acknowledgePcInterruptFlag() { PCIFR |= (1 << PCIF2); }
	struct BitBang { using Data = DataD7; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ain1 { using Data = DataD7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ain1; };
};
template<Peripheral p> struct SignalConnection<DataD7::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioD7::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataD7::Ain1, p> {
	static_assert((p == Peripheral::Ac),"GpioD7::Ain1 only connects to Ac!"); };

} // namespace modm::platform::detail
/// @endcond