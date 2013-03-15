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

#include "util/StringBuffer.h"

namespace util {

StringBuffer::StringBuffer() {
}

StringBuffer::StringBuffer(const char *str)
	: String(str)
{
}

StringBuffer::StringBuffer(const String &str)
	: String(str)
{
}

StringBuffer::StringBuffer(PgmSpaceString str)
	: String()
{
	operator <<(str);
}

void StringBuffer::clear() {
	String::operator =("");
}

char *StringBuffer::getBuffer() {
	return buffer;
}

StringBuffer &StringBuffer::operator <<(PgmSpaceString text) {
	unsigned int newlen = len + strlen(text);
	if (reserve(newlen)) {
		strcpy(buffer + len, text);
		len = newlen;
	}

	return *this;
}

StringBuffer &StringBuffer::operator <<(uint8_t data) {
	concat(data);
	return *this;
}

} // namespace util
