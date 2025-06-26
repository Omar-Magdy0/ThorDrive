/*
 * Copyright (c) 2009-2013, 2017, Fabian Greif
 * Copyright (c) 2011-2014, 2016-2017, Niklas Hauser
 * Copyright (c) 2017, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

// Avoid problems with poisoned defines from the the newer devices
#define __AVR_LIBC_DEPRECATED_ENABLE__	1

#include "uart0.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <modm/architecture/driver/atomic/queue.hpp>
#include <modm/architecture/interface/atomic_lock.hpp>
#include <modm/architecture/interface/interrupt.hpp>

#include "uart_defines.h"

static modm::atomic::Queue<uint8_t, modm::platform::Uart0::RxBufferSize> rxBuffer;
static uint8_t error;

// ----------------------------------------------------------------------------
MODM_ISR(USART0_RX)
{
	// first save the errors
	error |= UCSR0A & ((1 << FE0) | (1 << DOR0));
	// then read the buffer
	uint8_t data = UDR0;
	// push it into the buffer
	rxBuffer.push(data);
}

// ----------------------------------------------------------------------------
void
modm::platform::Uart0::initialize(uint16_t ubrr)
{
	atomic::Lock lock;
	// Set baud rate
	if (ubrr & 0x8000) {
		UCSR0A = (1 << U2X0);  //Enable 2x speed
		ubrr &= ~0x8000;
	}
	else {
		UCSR0A = 0;
	}
	UBRR0L = (uint8_t)  ubrr;
	UBRR0H = (uint8_t) (ubrr >> 8);

	// Enable USART receiver and transmitter and receive complete interrupt
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: asynchronous, 8data, no parity, 1stop bit
#ifdef URSEL0
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << URSEL0);
#else
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
#endif
}

// MARK: - read
bool
modm::platform::Uart0::read(uint8_t& data)
{
	if (rxBuffer.isEmpty())
		return false;

	data = rxBuffer.get();
	rxBuffer.pop();

	return true;
}

std::size_t
modm::platform::Uart0::read(uint8_t *buffer, std::size_t length)
{
	for (std::size_t i = 0; i < length; ++i)
	{
		if (rxBuffer.isEmpty()) {
			return i;
		}
		else {
			*buffer++ = rxBuffer.get();
			rxBuffer.pop();
		}
	}

	return length;
}

// MARK: - discard
std::size_t
modm::platform::Uart0::discardReceiveBuffer()
{
	std::size_t i(0);
	while(!rxBuffer.isEmpty())
	{
		rxBuffer.pop();
		++i;
	}

#if defined (RXC0)
	uint8_t c;
	while (UCSR0A & (1 << RXC0))
	{
		c = UDR0;
		(void) c;
	}
#endif

	return i;
}

// MARK: - error
uint8_t
modm::platform::Uart0::getErrorFlags()
{
	return error;
}

void
modm::platform::Uart0::acknowledgeErrorFlags()
{
	error = 0;
}
