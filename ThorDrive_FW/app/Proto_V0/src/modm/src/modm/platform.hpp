/*
 * Copyright (c) 2016, Sascha Schade
 * Copyright (c) 2017, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/architecture.hpp>

#include "platform/adc/adc.hpp"
#include "platform/adc/adc_interrupt.hpp"
#include "platform/clock/clock.hpp"
#include "platform/core/interrupts.hpp"
#include "platform/core/main.hpp"
#include "platform/gpio/base.hpp"
#include "platform/gpio/connector.hpp"
#include "platform/gpio/data.hpp"
#include "platform/gpio/define.h"
#include "platform/gpio/inverted.hpp"
#include "platform/gpio/open_drain.hpp"
#include "platform/gpio/pins.hpp"
#include "platform/gpio/port.hpp"
#include "platform/gpio/port_shim.hpp"
#include "platform/gpio/set.hpp"
#include "platform/gpio/software_port.hpp"
#include "platform/gpio/static.hpp"
#include "platform/gpio/unused.hpp"
#include "platform/uart/uart0.hpp"
#include "platform/uart/uart_defines.h"
