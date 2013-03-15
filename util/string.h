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

#ifndef UTIL_STRING_H_
#define UTIL_STRING_H_


#include "pgm_space.h"
#include <Print.h>
#include <WString.h>
#include <IPAddress.h>


/**
 * Mimics standard @a strncpy function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strncpy_P.
 *
 * @see strncpy_P
 *
 * @param dst buffer where copy string.
 * @param str source program space string.
 * @param size number of bytes to copy.
 * @return pointer to @a dst buffer.
 */
inline char *strncpy(char *dst, PgmSpaceString str, size_t size) {
	return strncpy_P(dst, reinterpret_cast<const char *>(str), size);
}

/**
 * Mimics standard @a strcpy function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strcpy_P.
 *
 * @see strcpy_P
 *
 * @param dst buffer where copy string.
 * @param str source program space string.
 * @return pointer to @a dst buffer.
 */
inline char *strcpy(char *dst, PgmSpaceString str) {
	return strcpy_P(dst, reinterpret_cast<const char *>(str));
}

/**
 * Mimics standard @a strlen function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strlen_P.
 *
 * @see strlen_P
 *
 * @param str source program space string.
 * @return number of characters in string pointed by @a str.
 */
inline size_t strlen(PgmSpaceString str) {
	return strlen_P(reinterpret_cast<const char *>(str));
}

/**
 * Mimics standard @a strcmp function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strcmp_P.
 *
 * @see strcmp
 * @see strcmp_P
 *
 * @param mstr string buffer in memory to compare.
 * @param pstr string buffer in program space memory to compare.
 * @return 0 if strings are equal, <0 if @a mstr is minor than @a pstr and >0
 * if @a mstr is greater than @a pstr.
 */
inline int strcmp(const char *mstr, PgmSpaceString pstr) {
	return strcmp_P(mstr, reinterpret_cast<const char *>(pstr));
}

/**
 * Mimics standard @a strncmp function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strncmp_P.
 *
 * @see strncmp
 * @see strncmp_P
 *
 * @param mstr string buffer in memory to compare.
 * @param pstr string buffer in program space memory to compare.
 * @return 0 if strings are equal, <0 if @a mstr is minor than @a pstr and >0
 * if @a mstr is greater than @a pstr.
 */
inline int strncmp(const char *mstr, PgmSpaceString pstr, size_t size) {
	return strncmp_P(mstr, reinterpret_cast<const char *>(pstr), size);
}

/**
 * Mimics standard @a strcat function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * Uses AVR program string function @a strcat_P.
 *
 * @see strcat
 * @see strcat_P
 *
 * @param dst destination string buffer.
 * @param str source program space string buffer.
 * @return pointer to destination string buffer.
 */
inline char *strcat(char *dst, PgmSpaceString str) {
	return strcat_P(dst, reinterpret_cast<const char *>(str));
}

/**
 * Mimics standard @a strtoul function but using @a __FlashStringHelper as
 * defined in @a WString.h
 *
 * @see strtoul
 *
 * @param str string buffer to parse.
 * @param end pointer to last character to parse. If NULL, string will be parsed
 * until an ending character or not digit found.
 * @param base number representation base.
 * @return value parsed, or 0 if an error ocurred.
 */
extern unsigned long strtoul(PgmSpaceString str, PgmSpaceString *end, size_t base);

namespace string {


	/**
	 * Prints @a c character to @a p, if @a c is a non-printable character, it's
	 * replaced with a <X> string.
	 * Example: '\r' prints as <CR>, '\\n' as <LF>, etc
	 *
	 * @param p object where to print character.
	 * @param c character to print.
	 */
	extern void printSpecialChar(Print &p, char c);

	/**
	 * Prints a string to @a p replacing non-printable characters with a <X>
	 * string.
	 * Example: '\r' prints as "<CR>", '\\n' as "<LF>", etc
	 *
	 * @param p object where to print character.
	 * @param str string to print.
	 */
	extern void printSpecialChars(Print &p, const char *str);


	/**
	 * Parses a decimal signed integer from @a str string.
	 *
	 * @param str string buffer to parse.
	 * @param v returned integer value.
	 * @return true if integer parsed correctly, false otherwise.
	 */
	template <typename T>
	inline bool parseInt(const char *str, T &v) {
		char *endptr;
		v = static_cast<T>(strtol(str, &endptr, 10));
		return (str != endptr);
	}

	/**
	 * Parses a decimal unsigned integer from @a str string.
	 *
	 * @param str string buffer to parse.
	 * @param v returned integer value.
	 * @return true if integer parsed correctly, false otherwise.
	 */
	template <typename T>
	inline bool parseUInt(const char *str, T &v) {
		char *endptr;
		v = static_cast<T>(strtoul(str, &endptr, 10));
		return (str != endptr);
	}


	/**
	 * Checks if @a value begins with @a str string.
	 *
	 * @param value string buffer to check.
	 * @param str prefix string.
	 * @return true if @a value begins with @a str string, false otherwise.
	 */
	inline bool beginsWith(const char *value, PgmSpaceString str) {
		return (strncmp(value, str, strlen(str) - 1) == 0);
	}

	/**
	 * Return pointer to ending string character (0x00).
	 *
	 * @param ptr string buffer.
	 * @return pointer to ending string character.
	 */
	extern char *endOfString(char *ptr);

	/**
	 * Return pointer to ending string character (0x00).
	 *
	 * @param ptr string buffer.
	 * @return pointer to ending string character.
	 */
	extern const char *endOfString(const char *ptr);

	/**
	 * Moves @a ptr pointer while character pointer is a space or tab.
	 *
	 * @param ptr string buffer.
	 * @return pointer first character that is not a space or tab.
	 */
	extern char *skipSpaces(char *ptr);

	/**
	 * Moves @a ptr pointer while character pointer is a space or tab.
	 *
	 * @param ptr string buffer.
	 * @return pointer first character that is not a space or tab.
	 */
	extern const char *skipSpaces(const char *ptr);

	/**
	 * Moves @a ptr until @a endc character or end of string found.
	 *
	 * @param ptr string buffer.
	 * @param endc character where to stop.
	 * @return pointer to first character equal to @a endc or end of string.
	 */
	extern char *skipUntil(char *ptr, char endc);

	/**
	 * Moves @a ptr until @a endc character or end of string found.
	 *
	 * @param ptr string buffer.
	 * @param endc character where to stop.
	 * @return pointer to first character equal to @a endc or end of string.
	 */
	extern const char *skipUntil(const char *ptr, char endc);

	/**
	 * Places an ending character (0x00) at first trailing space of string.
	 *
	 * @param ptr string buffer.
	 * @return pointer to ending of string.
	 */
	extern char *removeTrailingSpaces(char *ptr);

	/**
	 * Places an ending character (0x00) at first trailing space of string.
	 *
	 * @param ptr string buffer.
	 * @return pointer to ending of string.
	 */
	extern const char *removeTrailingSpaces(const char *ptr);
}


#endif /* UTIL_STRING_H_ */

