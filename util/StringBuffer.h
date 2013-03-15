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

#ifndef STRINGBUFFER_H_
#define STRINGBUFFER_H_

#include "pgm_space.h"
#include "string.h"

namespace util {

/**
 * Helper class to work with variable string buffers.
 * Currently it uses Arduino @a String as base class that provides all
 * functionality. This class only provides @a operator<< and support for using
 * @a PgmSpaceString.
 *
 * In a future, the idea is to rewrite it without requiring @a String class.
 */
class StringBuffer : public String {
public:
	StringBuffer();
	StringBuffer(const char *str);
	StringBuffer(const String &str);
	StringBuffer(PgmSpaceString str);

	void clear();

	char *getBuffer();

	StringBuffer &operator <<(PgmSpaceString text);
	StringBuffer &operator <<(uint8_t data);

	template<typename T>
	StringBuffer &operator <<(const T &data) {
		concat(data);
		return *this;
	}
};

} // namespace util

#endif /* STRINGBUFFER_H_ */
