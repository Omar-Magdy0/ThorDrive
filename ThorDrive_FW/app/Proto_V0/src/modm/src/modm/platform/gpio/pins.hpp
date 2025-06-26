/*
 * Copyright (c) 2021, Niklas Hauser
 * Copyright (c) 2022, Andrey Kunitsyn
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "data.hpp"
#include "static.hpp"

namespace modm::platform
{

/// @ingroup modm_platform_gpio
/// @{
using GpioB0 = GpioStatic<detail::DataB0>;
using GpioOutputB0 = GpioB0;
using GpioInputB0  = GpioB0;

using GpioB1 = GpioStatic<detail::DataB1>;
using GpioOutputB1 = GpioB1;
using GpioInputB1  = GpioB1;

using GpioB2 = GpioStatic<detail::DataB2>;
using GpioOutputB2 = GpioB2;
using GpioInputB2  = GpioB2;

using GpioB3 = GpioStatic<detail::DataB3>;
using GpioOutputB3 = GpioB3;
using GpioInputB3  = GpioB3;

using GpioB4 = GpioStatic<detail::DataB4>;
using GpioOutputB4 = GpioB4;
using GpioInputB4  = GpioB4;

using GpioB5 = GpioStatic<detail::DataB5>;
using GpioOutputB5 = GpioB5;
using GpioInputB5  = GpioB5;

using GpioB6 = GpioStatic<detail::DataB6>;
using GpioOutputB6 = GpioB6;
using GpioInputB6  = GpioB6;

using GpioB7 = GpioStatic<detail::DataB7>;
using GpioOutputB7 = GpioB7;
using GpioInputB7  = GpioB7;

using GpioC0 = GpioStatic<detail::DataC0>;
using GpioOutputC0 = GpioC0;
using GpioInputC0  = GpioC0;

using GpioC1 = GpioStatic<detail::DataC1>;
using GpioOutputC1 = GpioC1;
using GpioInputC1  = GpioC1;

using GpioC2 = GpioStatic<detail::DataC2>;
using GpioOutputC2 = GpioC2;
using GpioInputC2  = GpioC2;

using GpioC3 = GpioStatic<detail::DataC3>;
using GpioOutputC3 = GpioC3;
using GpioInputC3  = GpioC3;

using GpioC4 = GpioStatic<detail::DataC4>;
using GpioOutputC4 = GpioC4;
using GpioInputC4  = GpioC4;

using GpioC5 = GpioStatic<detail::DataC5>;
using GpioOutputC5 = GpioC5;
using GpioInputC5  = GpioC5;

using GpioC6 = GpioStatic<detail::DataC6>;
using GpioOutputC6 = GpioC6;
using GpioInputC6  = GpioC6;

using GpioD0 = GpioStatic<detail::DataD0>;
using GpioOutputD0 = GpioD0;
using GpioInputD0  = GpioD0;

using GpioD1 = GpioStatic<detail::DataD1>;
using GpioOutputD1 = GpioD1;
using GpioInputD1  = GpioD1;

using GpioD2 = GpioStatic<detail::DataD2>;
using GpioOutputD2 = GpioD2;
using GpioInputD2  = GpioD2;

using GpioD3 = GpioStatic<detail::DataD3>;
using GpioOutputD3 = GpioD3;
using GpioInputD3  = GpioD3;

using GpioD4 = GpioStatic<detail::DataD4>;
using GpioOutputD4 = GpioD4;
using GpioInputD4  = GpioD4;

using GpioD5 = GpioStatic<detail::DataD5>;
using GpioOutputD5 = GpioD5;
using GpioInputD5  = GpioD5;

using GpioD6 = GpioStatic<detail::DataD6>;
using GpioOutputD6 = GpioD6;
using GpioInputD6  = GpioD6;

using GpioD7 = GpioStatic<detail::DataD7>;
using GpioOutputD7 = GpioD7;
using GpioInputD7  = GpioD7;

/// @}

} // namespace modm::platform

