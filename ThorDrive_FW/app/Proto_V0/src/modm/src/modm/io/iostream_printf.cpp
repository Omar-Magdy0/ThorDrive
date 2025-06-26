/*
 * Copyright (c) 2019, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdarg.h>
#include <modm/architecture/interface/accessor.hpp>
#include <cmath>
#include "iostream.hpp"

namespace modm
{

void
IOStream::writeInteger(int16_t value)
{
	// hard coded for -32'768
	char str[7 + 1]; // +1 for '\0'
	itoa(value, str, 10);
	device->write(str);
}

void
IOStream::writeInteger(uint16_t value)
{
	// hard coded for 32'768
	char str[6 + 1]; // +1 for '\0'
	utoa(value, str, 10);
	device->write(str);
}

void
IOStream::writeInteger(int32_t value)
{
	// hard coded for -2147483648
	char str[11 + 1]; // +1 for '\0'
	ltoa(value, str, 10);
	device->write(str);
}

void
IOStream::writeInteger(uint32_t value)
{
	// hard coded for 4294967295
	char str[10 + 1]; // +1 for '\0'
	ultoa(value, str, 10);
	device->write(str);
}

} // namespace modm