/*
 * Copyright (c) 2009, Martin Rosekeit
 * Copyright (c) 2009-2011, 2017, Fabian Greif
 * Copyright (c) 2011-2017, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_AVR_INTERRUPTS_HPP
#define MODM_AVR_INTERRUPTS_HPP

#include <avr/interrupt.h>

namespace modm
{

namespace platform
{

/// @ingroup	modm_platform_core
/// @{

/// enables global interrupts
static inline void
enableInterrupts()
{
	sei();
}

/// disables global interrupts
static inline void
disableInterrupts()
{
	cli();
}

/// @}

}	// namespace platform

}	// namespace modm


#endif	// MODM_AVR_INTERRUPTS_HPP