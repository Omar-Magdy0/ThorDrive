/*
 * Copyright (c) 2017, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "define.h"
#include <modm/architecture/interface/gpio.hpp>

namespace modm::platform
{

/// @ingroup modm_platform_core
enum class
Peripheral
{
	BitBang,
	Ac,
	Adc,
	Clock,
	Core,
	Eeprom,
	Spi,
	Tc0,
	Tc1,
	Tc2,
	Twi,
	Usart0,
	Wdt,
};

/// @ingroup	modm_platform_gpio
struct Gpio
{
	/// Each Input Pin can be configured in one of these states.
	enum class
	InputType : uint8_t
	{
		Floating,	///< The input pin is left floating
		PullUp,		///< The input pin is pulled to Vcc
	};

	enum class
	OutputType : uint8_t
	{
		PushPull	///< push-pull on output
	};

	/// Each External Interrupt can be configured to trigger on these conditions.
	enum class
	InputTrigger : uint8_t
	{
		LowLevel = 0b00,	///< triggers **continuously** during low level
		BothEdges = 0b01,	///< triggers on both rising and falling edge
		FallingEdge = 0b10,	///< triggers on falling edge
		RisingEdge = 0b11,	///< triggers on rising edge
	};

	/// Available ports on this device.
	enum class
	Port
	{
		B,
		C,
		D,
	};

	enum class
	Signal
	{
		BitBang,
		Ain0,
		Ain1,
		Clk0,
		Icp,
		In0,
		In1,
		In2,
		In3,
		In4,
		In5,
		Miso,
		Mosi,
		Oca,
		Ocb,
		Rxd,
		Sck,
		Scl,
		Sda,
		Ss,
		T,
		Tosc1,
		Tosc2,
		Txd,
		Xck,
		Xtal1,
		Xtal2,
	};
};

}	// namespace modm::platform