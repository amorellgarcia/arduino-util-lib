////////////////////////////////////////////////////////////////////////////////
/// @section LICENSE                                                         ///
///                (C) Copyright 2013 Alejandro Morell Garcia                ///
///        Distributed under the Boost Software License, Version 1.0.        ///
///             (See accompanying file LICENSE_1_0.txt or copy at            ///
///                  http://www.boost.org/LICENSE_1_0.txt)                   ///
///                                                                          ///
/// @file                                                                    ///
/// @author  Alejandro Morell Garcia (http://github.com/amorellgarcia)       ///
/// @version 1.0                                                             ///
////////////////////////////////////////////////////////////////////////////////

#include "util/io.h"
#include "util/bitfield.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

namespace io {

int analogReadFast(uint8_t pin) {
	// Save default settings
	const uint8_t mask = bit(ADPS2)|bit(ADPS1)|bit(ADPS0);
	const uint8_t backup = (_SFR_BYTE(ADCSRA) & mask);

	// set prescale to 16
	setMaskValue(_SFR_BYTE(ADCSRA), bit(ADPS2), mask);

	int res = analogRead(pin);

	// Restore default settings
	setMaskValue(_SFR_BYTE(ADCSRA), backup, mask);

	return res;
}

} // namespace io
