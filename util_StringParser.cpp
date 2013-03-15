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

#include "util/StringParser.h"
#include "util/string.h"
#include <string.h>
#include <errno.h>
#include <Print.h>

namespace util {

StringParser::StringParser(const char *ptr, char separator)
	: m_ptr(ptr)
	, m_separator(separator)
	, m_index(0)
	, m_errorIndex(0)
	, m_errorReason(StringParser::OK)
{
}

StringParser::operator bool() const {
	return (m_errorIndex == 0);
}

inline bool StringParser::hasErrors() const {
	return !operator bool();
}

void StringParser::setSeparator(char separator) {
	m_separator = separator;
}

uint8_t StringParser::getTokenCount() const {
	uint8_t n = (*m_ptr != '\0' ? 1 : 0);

	bool parseQuote = false;
	for(const char *ptr = m_ptr; *ptr != '\0'; ++ptr) {
		if (*ptr == '"') {
			parseQuote = !parseQuote;
			continue;
		}

		if (!parseQuote && *ptr == m_separator) {
			++n;
		}
	}

	return n;
}

uint8_t StringParser::getTokenParsedCount() const {
	return m_index;
}

uint8_t StringParser::getErrorIndex() const {
	return m_errorIndex;
}

StringParser::error_reason_t StringParser::getErrorReason() const {
	return m_errorReason;
}

StringParser &StringParser::operator >>(char *dst) {
	incIndexAndCheckErrors();
	if (hasErrors()) {
		return *this;
	}

	// Check for invalid state
	if (dst == NULL) {
		m_errorIndex = m_index;
		m_errorReason = NULL_POINTER;
	} else {
		char endChar = m_separator;
		// State ok
		if (*m_ptr == '"') {
			++m_ptr;
			endChar = '"';
		}

		// Copy string until separator or end
		for(;*m_ptr != '\0' && *m_ptr != endChar; ++dst, ++m_ptr) {
			*dst = *m_ptr;
		}
		*dst = '\0';

		if (endChar == '"' && *m_ptr == '"') {
			++m_ptr;
		}

	}

	skipSeparator();
	return *this;
}

StringParser &StringParser::operator >>(String &dst) {
	incIndexAndCheckErrors();
	if (hasErrors()) {
		return *this;
	}

	// Some strings are delimited by quotes
	char endChar = m_separator;
	if (*m_ptr == '"') {
		++m_ptr;
		endChar = '"';
	}

	// Copy string until separator or end
	const char *endPtr = string::skipUntil(m_ptr, endChar);
	if (*endPtr == '\0') {
		dst = m_ptr;
	} else {
		dst = "";
		dst.reserve(endPtr - m_ptr);
		for(; m_ptr != endPtr; ++m_ptr) {
			dst.concat(*m_ptr);
		}
	}

	if (endChar == '"' && *m_ptr == '"') {
		++m_ptr;
	}

	skipSeparator();
	return *this;
}

long int StringParser::parseInt(char *endPtr, bool fSkipSeparator) {
	errno = 0;

	long int res = strtol(m_ptr, &endPtr, 10);
	if (errno == ERANGE) {
		m_errorIndex = m_index;
		m_errorReason = OVERFLOW;
	} else if (endPtr == m_ptr) {
		m_errorIndex = m_index;
		m_errorReason = TYPE_ERROR;
	}

	m_ptr = endPtr;
	if (fSkipSeparator) {
		skipSeparator();
	}
	return res;
}

void StringParser::printError(Print &p) const {
	p.print(F("index=")); p.print(m_errorIndex);
	if (hasErrors()) {
		p.print(F(", reason=")); p.print(m_errorReason);
	}
}

Print &operator <<(Print &p, const StringParser &s) {
	s.printError(p);
	return p;
}

StringParser &StringParser::operator >>(IPAddress &dst) {
	incIndexAndCheckErrors();
	if (hasErrors()) {
		return *this;
	}

	// Try to parse ip address
	// Parse string and check for overflow errors
	dst[0] = parseInt(NULL, false);
	for(uint8_t i = 1; i < 4 && !hasErrors(); i++) {
		if (m_ptr[0] == '.') {
			m_ptr++;
		} else {
			m_errorIndex = m_index;
			m_errorReason = TYPE_ERROR;
		}

		dst[i] = parseInt(NULL, false);
	}

	skipSeparator();
	return *this;
}

long int StringParser::parseIntValue() {
	incIndexAndCheckErrors();
	if (hasErrors()) {
		return *this;
	}

	// Find end of integer
	char *endPtr = strchr(m_ptr, m_separator);
	if (endPtr != NULL && endPtr != m_ptr) {
		--endPtr;
	}

	// Parse string and check for overflow errors
	return parseInt(endPtr);
}

StringParser &StringParser::operator >>(parse_function_t func) {
	incIndexAndCheckErrors();
	if (hasErrors()) {
		return *this;
	}

	// Check for invalid state
	if (func == NULL) {
		m_errorIndex = m_index;
		m_errorReason = NULL_POINTER;
	} else {
		m_errorReason = OK;
		const char *end = (*func)(m_ptr, m_errorReason);
		if (m_errorReason == OK) {
			m_ptr = end;
		} else {
			m_errorIndex = m_index;
		}
	}

	skipSeparator();
	return *this;
}

void StringParser::incIndexAndCheckErrors() {
	if (!hasErrors()) {
		++m_index;
		if (m_ptr == NULL) {
			m_errorIndex = m_index;
			m_errorReason = END_OF_STRING;
		} else {
			m_ptr = string::skipSpaces(m_ptr);
			if (*m_ptr == '\0') {
				m_errorIndex = m_index;
				m_errorReason = END_OF_STRING;
			}
		}
	}
}

void StringParser::skipSeparator() {
	if (hasErrors()) {
		// Do nothing
	} else if (m_ptr != NULL) {
		m_ptr = string::skipSpaces(m_ptr);
		if (*m_ptr == m_separator) {
			++m_ptr;
		} else if (*m_ptr != '\0') {
			m_errorIndex = m_index;
			m_errorReason = TYPE_ERROR;
		}
	}
}

} // namespace util
