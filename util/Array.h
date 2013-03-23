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
///                                                                          ///
/// @section DESCRIPTION                                                     ///
///                                                                          ///
/// Code related to array manipulation tasks.                                ///
////////////////////////////////////////////////////////////////////////////////

#ifndef UTIL_ARRAY_H_
#define UTIL_ARRAY_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/**
 * Calculates at compile time the array item count.
 *
 * @param item array.
 * @return number of items in array.
 */
#ifdef constexpr
template<typename T, size_t N>
inline constexpr size_t ArrayLength(const T (&)[N])  {
	return N;
}
#else
#define ArrayLength(array) (sizeof(array) / sizeof(array[0]))
#endif


namespace util {
namespace Array {


namespace detail {
template <size_t itemSize>
void CopyMemItems(void *array, size_t from, size_t to, size_t itemCount) {
	if (from != to) {
		const uintptr_t src = (uintptr_t)array + from * itemSize;
		const uintptr_t dst = (uintptr_t)array + to * itemSize;
		memmove((void *)dst, (void *)src, itemCount * itemSize);
	}
}
}


/**
 * Copy a number of items starting at @a from to position @a to.
 * Result array will contain:
 * @verbatim
 * array[to,to + itemCount] = array[from, from+itemCount]
 * @endverbatim
 *
 * Note: this function only copies memory of each item, so no operator = is
 * called. Be careful when using objects that require an special copy method.
 *
 * @param array 	array containing items
 * @param from 		first item index to be copied
 * @param to        position where will be copied the first item
 * @param itemCount number of items to be copied
 */
template<typename T>
inline void CopyMemItems(T *array, size_t from, size_t to, size_t itemCount) {
	detail::CopyMemItems<sizeof(T)>(array, from, to, itemCount);
}


/**
 * Copy a number of items starting at @a from to position @a to.
 * Result array will contain:
 * @verbatim
 * array[to,to + itemCount] = array[from, from+itemCount]
 * @endverbatim
 *
 * Uses operator =, so this function can be used to copy item objects that
 * override default copy operator.
 *
 * @param array 	array containing items
 * @param from 		first item index to be copied
 * @param to        position where will be copied the first item
 * @param itemCount number of items to be copied
 */
template <typename T>
void CopyItems(T *array, size_t from, size_t to, size_t itemCount) {
	if (from != to) {
		T *dst = array + to;
		const T *src = array + from;
		for (;itemCount > 0; --itemCount) {
			*dst++ = *src++;
		}
	}
}


} // namespace Array
} // namespace util

#endif // UTIL_ARRAY_H_
