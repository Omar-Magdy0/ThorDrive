/*
 * Copyright (c) 2009, Martin Rosekeit
 * Copyright (c) 2009-2012, 2017, Fabian Greif
 * Copyright (c) 2010, Georgi Grinshpun
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

static modm::atomic::Queue<uint8_t, modm::platform::Uart0::TxBufferSize> txBuffer;

// ----------------------------------------------------------------------------
MODM_ISR(USART0_UDRE)
{
	if (txBuffer.isEmpty())
	{
		// transmission finished, disable UDRE interrupt
		UCSR0B &= ~(1 << UDRIE0);
	}
	else {
		// get one byte from buffer and write it to the UART buffer
		// which starts the transmission
		UDR0 = txBuffer.get();
		txBuffer.pop();
	}
}

// MARK: - write blocking
void
modm::platform::Uart0::writeBlocking(uint8_t data)
{
	// wait until there is some place in the buffer
	while (!write(data))
		;

	// wait until everything has been sent
	while (!isWriteFinished())
		;
}

void
modm::platform::Uart0::writeBlocking(const uint8_t *data, std::size_t length)
{
	// first push everything into the buffer
	for (std::size_t i = 0; i < length; ++i)
	{
		while (!write(*data++))
			;
	}

	// then wait
	while (!isWriteFinished())
		;
}

void
modm::platform::Uart0::flushWriteBuffer()
{
	// just wait until the last byte has been sent
	while (!isWriteFinished())
		;
}

// MARK: - write
bool
modm::platform::Uart0::write(uint8_t data)
{
	if (!txBuffer.push(data))
		return false;

	::modm::atomic::Lock lock;

	// enable UDRE interrupt
	UCSR0B |= (1 << UDRIE0);

	return true;
}

std::size_t
modm::platform::Uart0::write(const uint8_t *data, std::size_t length)
{
	for (std::size_t i = 0; i < length; ++i)
	{
		if (!write(*data++))
		{
			return i;
		}
	}

	return length;
}

bool
modm::platform::Uart0::isWriteFinished()
{
	return (txBuffer.isEmpty() && !(UCSR0B & (1 << UDRIE0)));
}

// MARK: - discard
std::size_t
modm::platform::Uart0::discardTransmitBuffer()
{
	{
		::modm::atomic::Lock lock;
		UCSR0B &= ~(1 << UDRIE0);
	}

	std::size_t i = 0;
	while(!txBuffer.isEmpty())
	{
		txBuffer.pop();
		++i;
	}

	return i;
}
