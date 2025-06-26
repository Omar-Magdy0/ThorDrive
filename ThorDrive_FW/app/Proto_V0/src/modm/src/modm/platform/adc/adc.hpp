/*
 * Copyright (c) 2015-2017, Niklas Hauser
 * Copyright (c) 2016, Sascha Schade
 * Copyright (c) 2017, Fabian Greif
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_ATMEGA_ADC_HPP
#define MODM_ATMEGA_ADC_HPP

#include <modm/architecture/interface/adc.hpp>
#include <modm/architecture/interface/register.hpp>
#include <modm/platform/gpio/connector.hpp>
#include <modm/math/algorithm/prescaler.hpp>
//#include "../device.hpp"

#if defined (__AVR_ATmega64HVE__) || defined(__AVR_ATmega64HVE2__)
#	error "The ATmega64HVE2 is not supported by this ADC class."
#endif

namespace modm
{

namespace platform
{

/**
 * Generic Analog/Digital-Converter module
 *
 * This class aims at providing a common interface to all the different
 * register layouts of the ADC modules in most ATmegas.
 * It takes into consideration restrictions and extensions in ADC
 * functionality and provides the appropriate methods to configure them.
 *
 * This class enables you to address and use a broader array of ATmegas
 * with similar ADC functionality without changing a single line of code.
 *
 * For best use of this class, check your device's datasheet for the
 * supported functionality.
 *
 * ADC clock frequency should be between 50 and 200 kHz for maximum
 * resolution.
 * If less than the full resolution of 10 bits are
 * needed the frequency can be higher.
 *
 * @author	Niklas Hauser
 * @ingroup	modm_platform_adc
 */
class Adc : public modm::Adc
{
public:
	typedef uint8_t Channel;
	static constexpr uint8_t Resolution = 10;

	enum class
	Reference : uint8_t
	{
		ExternalRef = 0,
		InternalVcc = 0x40,
		Internal2V56 = 0xe0,
		Internal1V1 = 0xc0,
	};
	enum class
	InterruptFlag : uint8_t
	{
		All = (1<<ADIF),
	};
	MODM_FLAGS8(InterruptFlag);

private:
	enum class
	Prescaler : uint8_t
	{
		Div2 = 0x01,
		Div4 = 0x02,
		Div8 = 0x03,
		Div16 = 0x04,
		Div32 = 0x05,
		Div64 = 0x06,
		Div128 = 0x07,
	};

public:
	// start inherited documentation
	template< class... Signals >
	static void
	connect()
	{
		using Connector = GpioConnector<Peripheral::Adc, Signals...>;
		Connector::connect();
	}

	template< class SystemClock, frequency_t frequency=kHz(100), percent_t tolerance=pct(10) >
	static void
	initialize()
	{
		constexpr auto result = modm::Prescaler::from_power(SystemClock::Adc, frequency, 2, 128);
		assertBaudrateInTolerance< result.frequency, frequency, tolerance >();

		disable();
		setPrescaler(Prescaler{result.index});
		// enable the module
		ADCSRA |= (1<<ADEN);
	}

	static inline void
	disable()
	{
		ADCSRA &= ~(1<<ADEN);
	}


	static inline void
	startConversion()
	{
		acknowledgeInterruptFlag();
		ADCSRA |= (1<<ADSC);
	}

	static inline bool
	isConversionFinished()
	{
		return getInterruptFlag();
	}

	static inline uint16_t
	getValue()
	{
		return ADC;
	}


	/**
	 * Read the value an analog channel
	 *
	 * A normal conversion takes 13 ADC clock cycles. With a clock frequency
	 * of for example 200 kHz a conversion therefore needs 65 microseconds.
	 * This time increases with a lower frequency.
	 */
	static inline uint16_t
	readChannel(Channel channel)
	{
		if (!setChannel(channel)) return 0;

		startConversion();
		// wait until the conversion is finished
		while (!isConversionFinished())
			;

		return getValue();
	}


	static inline bool
	setChannel(Channel channel)
	{
		if (channel > 0x0f) return false;
		ADMUX = (ADMUX & ~0x1f) | (channel & 0x1f);
		return true;
	}

	static inline uint8_t
	getChannel()
	{
		return (ADMUX & 0x1f);
	}


	static inline void
	enableFreeRunningMode()
	{
		enableAutoTrigger();
		setAutoTriggerSource(0);
	}

	static inline void
	diableFreeRunningMode()
	{
		disableAutoTrigger();
	}


	static inline void
	setLeftAdjustResult()
	{
		ADMUX |= (1 << ADLAR);
	}

	static inline void
	setRightAdjustResult()
	{
		ADMUX &= ~(1 << ADLAR);
	}
	// stop inherited documentation

	/**
	 * voltage reference for the ADC
	 *
	 * The internal voltage reference options may not be used if an
	 * external reference voltage is being applied to the AREF pin.
	 */
	static inline void
	setReference(Reference reference)
	{
		ADMUX = (ADMUX & ~0xc0) | (uint8_t(reference) & 0xc0);
	}
	/// @return	`true` if the flag is set,
	///			`false` otherwise
	static inline bool
	getInterruptFlag()
	{
		return (ADCSRA & (1<<ADIF));
	}

	/// @return	`InterruptFlag::All` if the flag is set,
	///			`0` otherwise
	static inline InterruptFlag_t
	getInterruptFlags()
	{
		return InterruptFlag(ADCSRA & (1<<ADIF));
	}

	/// Clears the interrupt flag
	static inline void
	acknowledgeInterruptFlag()
	{
		ADCSRA &= ~(1<<ADIF);
	}

	/// Clears the interrupt flag if `flags` is set to `InterruptFlag::All`
	static inline void
	acknowledgeInterruptFlags(const InterruptFlag_t flags)
	{
		ADCSRA &= ~flags.value;
	}

	/// Enables the ADC Conversion Complete Interrupt
	static inline void
	enableInterrupt()
	{
		ADCSRA |= (1<<ADIE);
	}

	/// Disables the ADC Conversion Complete Interrupt
	static inline void
	disableInterrupt()
	{
		ADCSRA &= ~(1<<ADIE);
	}

	/**
	 * Enable auto triggering of the ADC
	 *
	 * The ADC will start a conversion on a positive edge of the
	 * selected trigger signal.
	 * @see setAutoTriggerSource
	 */
	static inline void
	enableAutoTrigger()
	{
		ADCSRA |= (1<<ADATE);
	}

	/// Disable auto triggering of the ADC
	static inline void
	disableAutoTrigger()
	{
		ADCSRA &= ~(1<<ADATE);
	}

	/**
	 * Selects which source will trigger an ADC conversion
	 *
	 * A conversion will be triggered by the rising edge of the
	 * selected Interrupt Flag. Note that switching from a trigger
	 * source that is cleared to a trigger source that is set, will
	 * generate a positive edge on the trigger signal.
	 * Set to 0 to enable Free Running Mode.
	 */
	static inline void
	setAutoTriggerSource(uint8_t source)
	{
		if (source > 0x07) return;
		ADCSRB = (ADCSRB & ~0x0f) | source;
	}
	// MARK: special operation modes
private:
	static inline void
	setPrescaler(Prescaler prescaler)
	{
		ADCSRA = (ADCSRA & ~0x07) | static_cast<uint8_t>(prescaler);
	}
};

}	// namespace platform

}	// namespace modm

#endif	// MODM_ATMEGA_ADC_HPP