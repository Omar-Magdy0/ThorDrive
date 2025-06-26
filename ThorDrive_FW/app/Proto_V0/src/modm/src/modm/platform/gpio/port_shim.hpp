/*
 * Copyright (c) 2016-2018, Niklas Hauser
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

template< Gpio::Port port >
struct GpioPortInfo;
template< class StartGpio, int8_t Width >
struct GpioSetShim
{
	static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, Width> check;
};

// ------ Port Width Information ------
template<>
struct GpioPortInfo<Gpio::Port::B>
{
	static constexpr int8_t Width = 8;
	static constexpr int8_t StartPin = 0;
	static constexpr int8_t EndPin = StartPin + Width;

	template< uint8_t QueryStartPin, int8_t QueryWidth >
	struct check
	{
		static constexpr bool isNormal = QueryWidth > 0;
		static constexpr bool isReversed = QueryWidth < 0;
		static constexpr int8_t width = isNormal ? QueryWidth : -QueryWidth;
		static_assert(isReversed or width <= Width,
			"GpioPort Width out of bounds! Maximum is 8.");

		static_assert(isReversed or (QueryStartPin + QueryWidth <= EndPin),
			"GpioPort StartPin + Width out of bounds! Maximum is 7.");
		static_assert(isNormal or (StartPin <= QueryStartPin + QueryWidth + 1),
			"GpioPort StartPin - Width out of bounds! Minimum is 0.");
	};
};
template<>
struct GpioPortInfo<Gpio::Port::C>
{
	static constexpr int8_t Width = 7;
	static constexpr int8_t StartPin = 0;
	static constexpr int8_t EndPin = StartPin + Width;

	template< uint8_t QueryStartPin, int8_t QueryWidth >
	struct check
	{
		static constexpr bool isNormal = QueryWidth > 0;
		static constexpr bool isReversed = QueryWidth < 0;
		static constexpr int8_t width = isNormal ? QueryWidth : -QueryWidth;
		static_assert(isReversed or width <= Width,
			"GpioPort Width out of bounds! Maximum is 7.");

		static_assert(isReversed or (QueryStartPin + QueryWidth <= EndPin),
			"GpioPort StartPin + Width out of bounds! Maximum is 6.");
		static_assert(isNormal or (StartPin <= QueryStartPin + QueryWidth + 1),
			"GpioPort StartPin - Width out of bounds! Minimum is 0.");
	};
};
template<>
struct GpioPortInfo<Gpio::Port::D>
{
	static constexpr int8_t Width = 8;
	static constexpr int8_t StartPin = 0;
	static constexpr int8_t EndPin = StartPin + Width;

	template< uint8_t QueryStartPin, int8_t QueryWidth >
	struct check
	{
		static constexpr bool isNormal = QueryWidth > 0;
		static constexpr bool isReversed = QueryWidth < 0;
		static constexpr int8_t width = isNormal ? QueryWidth : -QueryWidth;
		static_assert(isReversed or width <= Width,
			"GpioPort Width out of bounds! Maximum is 8.");

		static_assert(isReversed or (QueryStartPin + QueryWidth <= EndPin),
			"GpioPort StartPin + Width out of bounds! Maximum is 7.");
		static_assert(isNormal or (StartPin <= QueryStartPin + QueryWidth + 1),
			"GpioPort StartPin - Width out of bounds! Minimum is 0.");
	};
};
// ------ Translator classes from Gpio + Width -> GpioSet ------
template< class StartGpio, int8_t offset >
struct GpioShim
{
	static constexpr typename StartGpio::Port port = StartGpio::port;
	static constexpr uint16_t mask = (1ul << (StartGpio::pin + offset));
	static constexpr bool isInverted = StartGpio::isInverted;
};
template< class StartGpio >
struct GpioSetShim<StartGpio, -8> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>,
		GpioShim<StartGpio, -3>,
		GpioShim<StartGpio, -4>,
		GpioShim<StartGpio, -5>,
		GpioShim<StartGpio, -6>,
		GpioShim<StartGpio, -7>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -8> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -7> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>,
		GpioShim<StartGpio, -3>,
		GpioShim<StartGpio, -4>,
		GpioShim<StartGpio, -5>,
		GpioShim<StartGpio, -6>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -7> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -6> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>,
		GpioShim<StartGpio, -3>,
		GpioShim<StartGpio, -4>,
		GpioShim<StartGpio, -5>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -6> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -5> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>,
		GpioShim<StartGpio, -3>,
		GpioShim<StartGpio, -4>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -5> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -4> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>,
		GpioShim<StartGpio, -3>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -4> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -3> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>,
		GpioShim<StartGpio, -2>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -3> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -2> : public GpioSet<
		GpioShim<StartGpio, 0>,
		GpioShim<StartGpio, -1>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -2> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, -1> : public GpioSet<
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, -1> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 0> : public GpioSet<
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 0> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 1> : public GpioSet<
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 1> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 2> : public GpioSet<
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 2> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 3> : public GpioSet<
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 3> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 4> : public GpioSet<
		GpioShim<StartGpio, 3>,
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 4> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 5> : public GpioSet<
		GpioShim<StartGpio, 4>,
		GpioShim<StartGpio, 3>,
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 5> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 6> : public GpioSet<
		GpioShim<StartGpio, 5>,
		GpioShim<StartGpio, 4>,
		GpioShim<StartGpio, 3>,
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 6> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 7> : public GpioSet<
		GpioShim<StartGpio, 6>,
		GpioShim<StartGpio, 5>,
		GpioShim<StartGpio, 4>,
		GpioShim<StartGpio, 3>,
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 7> check; };
template< class StartGpio >
struct GpioSetShim<StartGpio, 8> : public GpioSet<
		GpioShim<StartGpio, 7>,
		GpioShim<StartGpio, 6>,
		GpioShim<StartGpio, 5>,
		GpioShim<StartGpio, 4>,
		GpioShim<StartGpio, 3>,
		GpioShim<StartGpio, 2>,
		GpioShim<StartGpio, 1>,
		GpioShim<StartGpio, 0>
		> { static typename GpioPortInfo<StartGpio::port>::template check<StartGpio::pin, 8> check; };
} // namespace modm::platform::detail
/// @endcond