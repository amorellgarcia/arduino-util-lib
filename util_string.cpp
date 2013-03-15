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

#include "util/string.h"
#include "util/sort.h"
#include <errno.h>

unsigned long strtoul(PgmSpaceString str, PgmSpaceString *end, size_t base) {
	const PgmSpace<char> *ptr = reinterpret_cast<const PgmSpace<char> *>(str);
	const PgmSpace<char> *ptrEnd = reinterpret_cast<const PgmSpace<char> *>(end);
	unsigned long res = 0;


	for (char c = *ptr; c != '\0' && ptr != ptrEnd; c = *(++ptr)) {
		int digit;
		if (isdigit(c)) {
			digit = (int)(c - '0');
		} else {
			digit = (int)(tolower(c) - 'a');
		}
		res += digit * base;
	}

	return res;
}

namespace string {

PGMSPACE_STRING(CR, "<CR>");
PGMSPACE_STRING(LF, "<LF>");

void printSpecialChar(Print &os, char c) {
	if (c == '\r') {
		os << CR;
	} else if (c == '\n') {
		os << LF;
	} else {
		os.print(c);
	}
}

void printSpecialChars(Print &os, const char *msg) {
	for(int i = 0; msg[i] != '\0'; i++) {
		printSpecialChar(os, msg[i]);
	}
}

String &showSpecialChars(String &s) {
	s.replace("\r", "<CR>");
	s.replace("\n", "<LF>");
	return s;
}

char *endOfString(char *ptr) {
	while (*ptr++ != '\0') { } 	// Forward pointer until end
	return ptr;
}

const char *endOfString(const char *ptr) {
	while (*ptr++ != '\0') { } 	// Forward pointer until end
	return ptr;
}

char *skipSpaces(char *ptr) {
	while (isblank(*ptr)) {
		++ptr;
	}

	return ptr;
}

const char *skipSpaces(const char *ptr) {
	while (isblank(*ptr)) {
		++ptr;
	}

	return ptr;
}


char *skipUntil(char *ptr, char endc) {
	while (*ptr != '\0' && *ptr != endc) {
		++ptr;
	}

	return ptr;
}

const char *skipUntil(const char *ptr, char endc) {
	while (*ptr != '\0' && *ptr != endc) {
		++ptr;
	}

	return ptr;
}

char *removeTrailingSpaces(char *ptr) {
	while (isblank(*ptr)) {
		--ptr;
	}

	return ptr;
}

const char *removeTrailingSpaces(const char *ptr) {
	while (isblank(*ptr)) {
		--ptr;
	}

	return ptr;
}

} // namespace string
