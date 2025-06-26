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

#ifndef MODM_AVR_GPIO_SOFTWARE_PORT_HPP
#define MODM_AVR_GPIO_SOFTWARE_PORT_HPP

#include "set.hpp"
#include <type_traits>

namespace modm
{

namespace platform
{

/**
 * Create an up to 16-bit port from arbitrary pins.
 *
 * This class optimizes the data type for the `read()` and `write()` methods.
 * Supplying up to 8 Gpios will use `uint8_t`, up to 16 Gpios `uint16_t`.
 *
 * @note Since the bit order is explicitly given by the order of template arguments,
 *       this class only supports `DataOrder::Normal`.
 *       If you need reverse bit order, reverse the order of `Gpios`!
 *
 * @tparam Gpios	Up to 16 GpioIO classes, ordered MSB to LSB
 *
 * @author	Niklas Hauser
 * @ingroup	modm_platform_gpio
 */
template< class... Gpios >
class SoftwareGpioPort : public ::modm::GpioPort, public GpioSet<Gpios...>
{
	using Set = GpioSet<Gpios...>;
public:
	using Set::width;
	static_assert(width <= 16, "Only a maximum of 16 pins are supported by this Port!");
	using PortType = std::conditional_t< (width > 8),
										 uint16_t,
										 uint8_t >;

protected:
	static constexpr int8_t shift_masks[3][width] = {
		{(Gpios::port == Set::Port::B ? Gpios::pin : -1)...},
		{(Gpios::port == Set::Port::C ? Gpios::pin : -1)...},
		{(Gpios::port == Set::Port::D ? Gpios::pin : -1)...},
	};
	static constexpr int8_t shift_mask(uint8_t id, uint8_t pos) { return shift_masks[id][width - 1 - pos]; }
	using Set::mask;
	using Set::inverted;

public:
	static PortType isSet()
	{
		PortType r{0};
		if constexpr (mask(0)) {
			const uint8_t p = (PORTB & mask(0)) ^ inverted(0);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(0, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(0, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(0, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(0, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(0, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(0, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(0, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(0, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(0, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(0, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(0, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(0, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(0, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(0, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(0, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(0, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		if constexpr (mask(1)) {
			const uint8_t p = (PORTC & mask(1)) ^ inverted(1);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(1, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(1, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(1, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(1, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(1, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(1, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(1, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(1, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(1, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(1, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(1, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(1, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(1, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(1, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(1, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(1, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		if constexpr (mask(2)) {
			const uint8_t p = (PORTD & mask(2)) ^ inverted(2);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(2, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(2, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(2, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(2, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(2, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(2, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(2, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(2, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(2, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(2, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(2, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(2, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(2, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(2, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(2, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(2, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		return r;
	}

	static void write(PortType data)
	{
		if constexpr (mask(0)) { uint8_t p{0};
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(0, 0); pos >= 0) p |= (data & (1ul << 0)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(0, 1); pos >= 0) p |= (data & (1ul << 1)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(0, 2); pos >= 0) p |= (data & (1ul << 2)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(0, 3); pos >= 0) p |= (data & (1ul << 3)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(0, 4); pos >= 0) p |= (data & (1ul << 4)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(0, 5); pos >= 0) p |= (data & (1ul << 5)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(0, 6); pos >= 0) p |= (data & (1ul << 6)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(0, 7); pos >= 0) p |= (data & (1ul << 7)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(0, 8); pos >= 0) p |= (data & (1ul << 8)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(0, 9); pos >= 0) p |= (data & (1ul << 9)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(0, 10); pos >= 0) p |= (data & (1ul << 10)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(0, 11); pos >= 0) p |= (data & (1ul << 11)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(0, 12); pos >= 0) p |= (data & (1ul << 12)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(0, 13); pos >= 0) p |= (data & (1ul << 13)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(0, 14); pos >= 0) p |= (data & (1ul << 14)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(0, 15); pos >= 0) p |= (data & (1ul << 15)) ? (1ul << pos) : (1ul << (pos + 16));
			PORTB = (PORTB & ~mask(0)) | ((p & mask(0)) ^ inverted(0));
		}
		if constexpr (mask(1)) { uint8_t p{0};
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(1, 0); pos >= 0) p |= (data & (1ul << 0)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(1, 1); pos >= 0) p |= (data & (1ul << 1)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(1, 2); pos >= 0) p |= (data & (1ul << 2)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(1, 3); pos >= 0) p |= (data & (1ul << 3)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(1, 4); pos >= 0) p |= (data & (1ul << 4)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(1, 5); pos >= 0) p |= (data & (1ul << 5)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(1, 6); pos >= 0) p |= (data & (1ul << 6)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(1, 7); pos >= 0) p |= (data & (1ul << 7)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(1, 8); pos >= 0) p |= (data & (1ul << 8)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(1, 9); pos >= 0) p |= (data & (1ul << 9)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(1, 10); pos >= 0) p |= (data & (1ul << 10)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(1, 11); pos >= 0) p |= (data & (1ul << 11)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(1, 12); pos >= 0) p |= (data & (1ul << 12)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(1, 13); pos >= 0) p |= (data & (1ul << 13)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(1, 14); pos >= 0) p |= (data & (1ul << 14)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(1, 15); pos >= 0) p |= (data & (1ul << 15)) ? (1ul << pos) : (1ul << (pos + 16));
			PORTC = (PORTC & ~mask(1)) | ((p & mask(1)) ^ inverted(1));
		}
		if constexpr (mask(2)) { uint8_t p{0};
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(2, 0); pos >= 0) p |= (data & (1ul << 0)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(2, 1); pos >= 0) p |= (data & (1ul << 1)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(2, 2); pos >= 0) p |= (data & (1ul << 2)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(2, 3); pos >= 0) p |= (data & (1ul << 3)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(2, 4); pos >= 0) p |= (data & (1ul << 4)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(2, 5); pos >= 0) p |= (data & (1ul << 5)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(2, 6); pos >= 0) p |= (data & (1ul << 6)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(2, 7); pos >= 0) p |= (data & (1ul << 7)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(2, 8); pos >= 0) p |= (data & (1ul << 8)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(2, 9); pos >= 0) p |= (data & (1ul << 9)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(2, 10); pos >= 0) p |= (data & (1ul << 10)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(2, 11); pos >= 0) p |= (data & (1ul << 11)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(2, 12); pos >= 0) p |= (data & (1ul << 12)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(2, 13); pos >= 0) p |= (data & (1ul << 13)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(2, 14); pos >= 0) p |= (data & (1ul << 14)) ? (1ul << pos) : (1ul << (pos + 16));
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(2, 15); pos >= 0) p |= (data & (1ul << 15)) ? (1ul << pos) : (1ul << (pos + 16));
			PORTD = (PORTD & ~mask(2)) | ((p & mask(2)) ^ inverted(2));
		}
	}

	static PortType read()
	{
		PortType r{0};
		if constexpr (mask(0)) {
			const uint8_t p = (PINB & mask(0)) ^ inverted(0);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(0, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(0, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(0, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(0, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(0, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(0, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(0, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(0, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(0, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(0, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(0, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(0, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(0, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(0, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(0, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(0, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		if constexpr (mask(1)) {
			const uint8_t p = (PINC & mask(1)) ^ inverted(1);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(1, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(1, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(1, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(1, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(1, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(1, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(1, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(1, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(1, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(1, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(1, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(1, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(1, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(1, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(1, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(1, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		if constexpr (mask(2)) {
			const uint8_t p = (PIND & mask(2)) ^ inverted(2);
			if constexpr (0 < width) if constexpr (constexpr auto pos = shift_mask(2, 0); pos >= 0) r |= ((p >> pos) & 1) << 0;
			if constexpr (1 < width) if constexpr (constexpr auto pos = shift_mask(2, 1); pos >= 0) r |= ((p >> pos) & 1) << 1;
			if constexpr (2 < width) if constexpr (constexpr auto pos = shift_mask(2, 2); pos >= 0) r |= ((p >> pos) & 1) << 2;
			if constexpr (3 < width) if constexpr (constexpr auto pos = shift_mask(2, 3); pos >= 0) r |= ((p >> pos) & 1) << 3;
			if constexpr (4 < width) if constexpr (constexpr auto pos = shift_mask(2, 4); pos >= 0) r |= ((p >> pos) & 1) << 4;
			if constexpr (5 < width) if constexpr (constexpr auto pos = shift_mask(2, 5); pos >= 0) r |= ((p >> pos) & 1) << 5;
			if constexpr (6 < width) if constexpr (constexpr auto pos = shift_mask(2, 6); pos >= 0) r |= ((p >> pos) & 1) << 6;
			if constexpr (7 < width) if constexpr (constexpr auto pos = shift_mask(2, 7); pos >= 0) r |= ((p >> pos) & 1) << 7;
			if constexpr (8 < width) if constexpr (constexpr auto pos = shift_mask(2, 8); pos >= 0) r |= ((p >> pos) & 1) << 8;
			if constexpr (9 < width) if constexpr (constexpr auto pos = shift_mask(2, 9); pos >= 0) r |= ((p >> pos) & 1) << 9;
			if constexpr (10 < width) if constexpr (constexpr auto pos = shift_mask(2, 10); pos >= 0) r |= ((p >> pos) & 1) << 10;
			if constexpr (11 < width) if constexpr (constexpr auto pos = shift_mask(2, 11); pos >= 0) r |= ((p >> pos) & 1) << 11;
			if constexpr (12 < width) if constexpr (constexpr auto pos = shift_mask(2, 12); pos >= 0) r |= ((p >> pos) & 1) << 12;
			if constexpr (13 < width) if constexpr (constexpr auto pos = shift_mask(2, 13); pos >= 0) r |= ((p >> pos) & 1) << 13;
			if constexpr (14 < width) if constexpr (constexpr auto pos = shift_mask(2, 14); pos >= 0) r |= ((p >> pos) & 1) << 14;
			if constexpr (15 < width) if constexpr (constexpr auto pos = shift_mask(2, 15); pos >= 0) r |= ((p >> pos) & 1) << 15;
		}
		return r;
	}
};

} // namespace platform

} // namespace modm

#endif // MODM_AVR_GPIO_SOFTWARE_PORT_HPP