/*
 * Copyright (c) 2017-2018, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "port_shim.hpp"
#include "set.hpp"
#include <modm/math/utils/bit_operation.hpp>

namespace modm::platform
{

/// @ingroup modm_platform_gpio
template< class StartGpio, int8_t Width >
class GpioPort : public ::modm::GpioPort/** @cond */, public detail::GpioSetShim<StartGpio, Width>/** @endcond */
{
	using PinSet = detail::GpioSetShim<StartGpio, Width>;
public:
	using PinSet::width;
	static_assert(width <= 8, "Only a maximum of 8 pins are supported by GpioPort!");
	using PortType = uint8_t;

protected:
	using PinSet::mask;
	using PinSet::inverted;
	static constexpr uint8_t StartPin = Width > 0 ? StartGpio::pin : StartGpio::pin - width + 1;
	static constexpr uint8_t StartPinReversed = (4 - StartPin - width) + 4;

public:
	static PortType isSet()
	{
		uint8_t r{0};
		if constexpr (mask(0)) r = (PORTB & mask(0)) ^ inverted(0);
		if constexpr (mask(1)) r = (PORTC & mask(1)) ^ inverted(1);
		if constexpr (mask(2)) r = (PORTD & mask(2)) ^ inverted(2);
		if constexpr (Width < 0)
			 return bitReverse(r) >> StartPinReversed;
		else return            r  >> StartPin;
	}

	static PortType read()
	{
		uint8_t r{0};
		if constexpr (mask(0)) r = (PINB & mask(0)) ^ inverted(0);
		if constexpr (mask(1)) r = (PINC & mask(1)) ^ inverted(1);
		if constexpr (mask(2)) r = (PIND & mask(2)) ^ inverted(2);
		if constexpr (Width < 0)
			 return bitReverse(r) >> StartPinReversed;
		else return            r  >> StartPin;
	}

	static void write(PortType data)
	{
		uint8_t p;
		if constexpr (Width < 0)
			 p = bitReverse(uint8_t(data << StartPinReversed));
		else p =            uint8_t(data << StartPin);
		if constexpr (mask(0)) PORTB = (PORTB & ~mask(0)) | ((p & mask(0)) ^ inverted(0));
		if constexpr (mask(1)) PORTC = (PORTC & ~mask(1)) | ((p & mask(1)) ^ inverted(1));
		if constexpr (mask(2)) PORTD = (PORTD & ~mask(2)) | ((p & mask(2)) ^ inverted(2));
	}
};

} // namespace modm::platform