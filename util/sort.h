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

#ifndef UTIL_SORT_H_
#define UTIL_SORT_H_


#include <stdlib.h>


namespace util {

	template <typename TKey, typename TElem, int (*cmp_func)(const TKey *, const TElem *)>
	int cmp_func_wrapper(const void *vkey, const void *velem) {
		const TKey *key = reinterpret_cast<const TKey *>(vkey);
		const TElem *elem = reinterpret_cast<const TElem *>(velem);
		return (*cmp_func)(key, elem);
	}

	template <typename TKey, typename TElem, int (*cmp_func)(const TKey *, const TElem *)>
	bool binary_search(const TKey *key, const TElem *base, size_t count,
			size_t &indexFound)
	{
		void *res = bsearch(key,
				reinterpret_cast<const void *>(base), count,
				sizeof(TElem),
				&cmp_func_wrapper<TKey, TElem, cmp_func>);
		if (res != NULL) {
			indexFound = ((uintptr_t)res - (uintptr_t)base) / sizeof(TElem);
			return true;
		}

		return false;
	}

	//	template <typename TElem, typename TKey>
	//	static bool binary_search(size_t &index, const TElem *array, size_t arraySize, const TKey key,
	//			int (*cmp_func)(const TElem, const TKey))
	//	{
	//		size_t i = 0, j = arraySize;
	//		while (j >= i) {
	//			size_t mid = i + (i - j) / 2;
	//
	//			int cmp = (*cmp_func)(array[mid], key);
	//			if (cmp < 0) {
	//				i = mid + 1;
	//			} else if (cmp > 0) {
	//				j = mid - 1;
	//			} else {
	//				index = mid;
	//				return true;
	//			}
	//		}
	//
	//		return false;
	//	}

} // namespace sort


#endif // UTIL_SORT_H_
