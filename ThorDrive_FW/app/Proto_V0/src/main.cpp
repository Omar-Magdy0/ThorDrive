/*
 * Copyright (c) 2013-2014, Kevin Läufer
 * Copyright (c) 2013, 2016-2017, Niklas Hauser
 * Copyright (c) 2014, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

// Inspired by: http://arduino.cc/en/Tutorial/Blink

#include <modm/platform.hpp>
#include <cstdio>
#include <modm/debug/logger.hpp>
#include "thorHal/hal.h"
#include <avr/io.h>
#include "module/systemCtrl.h"

using namespace modm::platform;
using namespace std::chrono_literals;

systemCtrl_t systemCtrl;
#include "module/pmsmTrapCom.h"

using namespace modm::platform;
using namespace modm::literals;

// Create a new UART object and configure it to a baudrate of 115200
modm::IODeviceWrapper< Uart0, modm::IOBuffer::BlockIfFull > loggerDevice;

// Set all four logger streams to use the UART
modm::log::Logger modm::log::debug(loggerDevice);
modm::log::Logger modm::log::info(loggerDevice);
modm::log::Logger modm::log::warning(loggerDevice);
modm::log::Logger modm::log::error(loggerDevice);

// Set the log level
#undef	MODM_LOG_LEVEL
#define	MODM_LOG_LEVEL modm::log::DEBUG

int main()
{
	pmsmTrapCom.init();
	Uart0::connect<GpioD1::Txd, GpioD0::Rxd>();
	Uart0::initialize<SystemClock, 9600_Bd>();

	// Enable interrupts, this is needed for every buffered UART
	enableInterrupts();

	while (true)
	{
		char sad[20];
		sprintf(sad, "ICR1 = %u", (uint16_t)pmsmTrapCom.effDuty_fixed_Max);
		MODM_LOG_DEBUG   << "debug : "  <<  sad << modm::endl;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				pmsmTrapCom.driverWrite(pmsmTrapCom.effDuty_fixed_Max*(j&&4),pmsmTrapCom.effDuty_fixed_Max*(j&&2),pmsmTrapCom.effDuty_fixed_Max*(j&&1), (i&&4), (i&&2), (i&&1));
				// Use the logging streams to print some messages.
				// Change MODM_LOG_LEVEL above to enable or disable these messages
				MODM_LOG_DEBUG   << "debug : "  << j << " ; " << i << modm::endl;
				modm::delay(0.5s);
			}
		}

	}
}
