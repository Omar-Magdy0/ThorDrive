/*
 * Copyright (c) 2018, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_AVR_GPIO_SET_HPP
#define MODM_AVR_GPIO_SET_HPP

#include "base.hpp"

namespace modm
{

namespace platform
{

/// @ingroup modm_platform_gpio
template< class... Gpios >
class GpioSet : public Gpio
{
protected:
	static constexpr uint8_t inverteds[3] = {
		(((Gpios::port == Port::B and Gpios::isInverted) ? Gpios::mask : 0) | ...),
		(((Gpios::port == Port::C and Gpios::isInverted) ? Gpios::mask : 0) | ...),
		(((Gpios::port == Port::D and Gpios::isInverted) ? Gpios::mask : 0) | ...),
	};
	static constexpr uint8_t inverted(uint8_t id) { return inverteds[id]; }

	static constexpr uint8_t masks[3] = {
		(((Gpios::port == Port::B) ? Gpios::mask : 0) | ...),
		(((Gpios::port == Port::C) ? Gpios::mask : 0) | ...),
		(((Gpios::port == Port::D) ? Gpios::mask : 0) | ...),
	};
	static constexpr uint8_t mask(uint8_t id) { return masks[id]; }
	static constexpr uint8_t numberOfPorts() {
		uint8_t r{0};
		for (const auto &m: masks) r += (m) ? 1 : 0;
		return r;
	}

public:
	static constexpr uint8_t width = sizeof...(Gpios);
	static constexpr uint8_t number_of_ports = numberOfPorts();

public:
	static void setOutput()
	{
		if constexpr (mask(0)) { DDRB |= mask(0); }
		if constexpr (mask(1)) { DDRC |= mask(1); }
		if constexpr (mask(2)) { DDRD |= mask(2); }
	}

	static void setOutput(bool status)
	{
		set(status);
		setOutput();
	}

	static void setOutput(OutputType)
	{
		setOutput();
	}

	static void configure(OutputType)
	{
		setOutput();
	}

	static void setInput()
	{
		if constexpr (mask(0)) DDRB &= ~mask(0);
		if constexpr (mask(1)) DDRC &= ~mask(1);
		if constexpr (mask(2)) DDRD &= ~mask(2);
	}

	static void setInput(InputType type)
	{
		setInput();
		configure(type);
	}

	static void configure(InputType type)
	{
		if (type == InputType::PullUp) {
			if constexpr (mask(0)) PORTB |= mask(0);
			if constexpr (mask(1)) PORTC |= mask(1);
			if constexpr (mask(2)) PORTD |= mask(2);
		} else {
			if constexpr (mask(0)) PORTB &= ~mask(0);
			if constexpr (mask(1)) PORTC &= ~mask(1);
			if constexpr (mask(2)) PORTD &= ~mask(2);
		}
	}

	static void set()
	{
		if constexpr (mask(0)) PORTB = (PORTB & ~mask(0)) | (mask(0) ^ inverted(0));
		if constexpr (mask(1)) PORTC = (PORTC & ~mask(1)) | (mask(1) ^ inverted(1));
		if constexpr (mask(2)) PORTD = (PORTD & ~mask(2)) | (mask(2) ^ inverted(2));
	}

	static void set(bool status)
	{
		if (status) set();
		else        reset();
	}

	static void reset()
	{
		if constexpr (mask(0)) PORTB = (PORTB & ~mask(0)) | inverted(0);
		if constexpr (mask(1)) PORTC = (PORTC & ~mask(1)) | inverted(1);
		if constexpr (mask(2)) PORTD = (PORTD & ~mask(2)) | inverted(2);
	}

	static void toggle()
	{
		if constexpr (mask(0)) PINB = mask(0);
		if constexpr (mask(1)) PINC = mask(1);
		if constexpr (mask(2)) PIND = mask(2);
	}
};

} // namespace platform

} // namespace modm

#endif // MODM_AVR_GPIO_SET_HPP