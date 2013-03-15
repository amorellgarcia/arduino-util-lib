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

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

namespace util {

bool isTimeOverflow(const unsigned long &before, const unsigned long &after) {
	return (before > after);
}

unsigned long elapsedTime(const unsigned long &before, const unsigned long &after) {
	if (before <= after) {
		return (after - before);
	} else {
		unsigned long max = static_cast<unsigned long>(0) - 1;
		return (before + (max - after));
	}
}

bool timedOut(const unsigned long &start, const unsigned int &timeoutMs) {
	return (timeoutMs > 0 && elapsedTime(start, millis()) >= timeoutMs);
}

} // namespace util
