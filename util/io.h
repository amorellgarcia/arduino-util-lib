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

#ifndef UTIL_IO_H_
#define UTIL_IO_H_

#include <stdint.h>

namespace io {

/**
 * Read ADC value at @a pin using a fast prescaler configuration.
 *
 * @param pin io port to use.
 * @return ADC read value.
 */
extern int analogReadFast(uint8_t pin);

} // namespace io

#endif /* UTIL_IO_H_ */
