/*
 * Copyright (c) 2024 Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include <chrono>
#include <ctime>
namespace modm
{

/// @ingroup modm_io
/// @{

template< class Rep, class Period >
inline modm::IOStream&
operator << (modm::IOStream& s, const std::chrono::duration<Rep, Period>& d)
{
	s << d.count();

	if constexpr (std::is_same_v<typename Period::type, std::atto>)			s << "as";
	if constexpr (std::is_same_v<typename Period::type, std::femto>)		s << "fs";
	if constexpr (std::is_same_v<typename Period::type, std::pico>)			s << "ps";
	if constexpr (std::is_same_v<typename Period::type, std::nano>)			s << "ns";
	if constexpr (std::is_same_v<typename Period::type, std::micro>)		s << "us";
	if constexpr (std::is_same_v<typename Period::type, std::milli>)		s << "ms";
	if constexpr (std::is_same_v<typename Period::type, std::centi>)		s << "cs";
	if constexpr (std::is_same_v<typename Period::type, std::deci>)			s << "ds";
	if constexpr (std::is_same_v<typename Period::type, std::ratio<1>>)		s << 's';
	if constexpr (std::is_same_v<typename Period::type, std::deca>)			s << "as";
	if constexpr (std::is_same_v<typename Period::type, std::hecto>)		s << "hs";
	if constexpr (std::is_same_v<typename Period::type, std::kilo>)			s << "ks";
	if constexpr (std::is_same_v<typename Period::type, std::mega>)			s << "Ms";
	if constexpr (std::is_same_v<typename Period::type, std::giga>)			s << "Gs";
	if constexpr (std::is_same_v<typename Period::type, std::tera>)			s << "Ts";
	if constexpr (std::is_same_v<typename Period::type, std::peta>)			s << "Ps";
	if constexpr (std::is_same_v<typename Period::type, std::exa>)			s << "Es";

	if constexpr (std::is_same_v<typename Period::type, std::ratio<60>>)	s << "min";
	if constexpr (std::is_same_v<typename Period::type, std::ratio<3600>>)	s << 'h';
	if constexpr (std::is_same_v<typename Period::type, std::ratio<86400>>)	s << 'd';

	return s;
}

template< class Clock, class Duration >
modm::IOStream&
operator << (modm::IOStream& s, const std::chrono::time_point<Clock, Duration>& tp)
{
	return s << tp.time_since_epoch();
}

inline modm::IOStream&
operator << (modm::IOStream& s, const std::tm& tm)
{
	s << (tm.tm_year + 1900u) << '-' << tm.tm_mon << '-' << tm.tm_mday << ' ';
	s << tm.tm_hour << ':' << tm.tm_min << ':' << tm.tm_sec;
	return s;
}

/// @}

}


