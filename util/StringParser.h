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

#ifndef UTIL_STRINGPARSER_H_
#define UTIL_STRINGPARSER_H_

#include <stdint.h>

class String;
class IPAddress;
class Print;

namespace util {


/**
 * Helper class to tokenize or
 */
class StringParser {
public:
	enum error_reason_t {
		OK,
		TYPE_ERROR,
		NULL_POINTER,
		OVERFLOW,
		END_OF_STRING,
		NOT_MATCH
	};

	typedef const char * (*parse_function_t)(const char *str, error_reason_t &errorReason);

public:
	StringParser(const char *ptr, char separator);

	operator bool() const;
	bool hasErrors() const;

	void setSeparator(char separator);
	uint8_t getTokenCount() const;

	uint8_t getTokenParsedCount() const;

	uint8_t getErrorIndex() const;

	error_reason_t getErrorReason() const;

	StringParser &operator >>(char *dst);
	StringParser &operator >>(String &dst);
	StringParser &operator >>(IPAddress &dst);

	template <typename IntType>
	StringParser &operator >>(IntType &dst);

	StringParser &operator >>(parse_function_t func);

	void printError(Print &) const;

protected:
	void incIndexAndCheckErrors();
	void skipSeparator();
	long int parseIntValue();
	long int parseInt(char *endPtr, bool fSkipSeparator = true);

protected:
	const char *m_ptr;
	char m_separator;
	uint8_t m_index;
	uint8_t m_errorIndex;
	error_reason_t m_errorReason;
};

template <typename IntType>
StringParser &StringParser::operator >>(IntType &dst) {
	dst = parseIntValue();
	return *this;
}

} // namespace util

extern Print &operator <<(Print &, const util::StringParser &s);


#endif /* STRINGTOKENIZER_H_ */
