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

#ifndef UTIL_PRINT_HPP_
#define UTIL_PRINT_HPP_

#include "detail/pstrings.h"
#include <Print.h>

#define PRINT_VARIABLE(p, x) p.print(#x "="); p.println(x)

template <typename T>
inline void PrintValue(Print &p, const T &value) {
	p.print(value);
}

template <typename T>
void PrintArray(Print &p, const T *array, size_t length) {
	p.print('{');
	if (length > 0) {
		PrintValue(p, array[0]);
		for (size_t i = 1; i < length; ++i) {
			p.print(::util::detail::SEPARATOR_COMMA);
			PrintValue(p, array[i]);
		}
	}
	p.print('}');
}

template <typename T, size_t length>
inline void PrintArray(Print &p, const T (&array)[length]) {
	PrintArray(p, array, length);
}


#endif // UTIL_PRINT_HPP_
