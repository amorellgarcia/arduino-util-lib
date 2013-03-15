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
/// Bit manipulation macros/functions.                                       ///
////////////////////////////////////////////////////////////////////////////////

#ifndef UTIL_BITFIELD_H_
#define UTIL_BITFIELD_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


/**
 * Define a number using it's binary representation.
 */
template<uintmax_t N>
struct binary {
	enum {
		value = (N % 2) + (binary<N / 2>::value << 1)
	};
};

template<>
struct binary<0> {
	enum {
		value = 0
	};
};


// TODO use constexpr functions for C++11
//#ifdef constexpr
//
//template <typename T>
//inline constexpr void clrBit(T &value, const int bit) {
//	value = static_cast<T>(value & ~(1 << bit));
//}
//
//template <typename T>
//inline constexpr void setBit(T &value, const int bit) {
//	value = static_cast<T>(value | (1 << bit));
//}
//
//#else


#ifndef bit
#define bit(bitnumber)					(1 << bitnumber)
#endif
#ifndef clrBit
#define clrBit(value, bn) 				(value) &= ~bit(bn)
#endif
#ifndef setBit
#define setBit(value, bn) 				(value) |= bit(bn)
#endif
#ifndef isSetBit
#define isSetBit(value, bn)	            (((value) & bit(bn)) != 0)
#endif
#ifndef isClrBit
#define isClrBit(value, bn)	            (((value) & bit(bn)) == 0)
#endif

#ifndef lowBitmask
#define lowBitmask(bn)                 ((1 << (bn)) - 1)
#endif
#ifndef highBitmask
#define highBitmask(bn)                ~(lowBRangeMask(bn))
#endif

#ifndef clrMask
#define clrMask(dst, mask) 				(dst) &= ~(mask)
#endif
#ifndef setMask
#define setMask(dst, mask)             (dst) |= (mask)
#endif
#ifndef setMaskValue
#define setMaskValue(dst, value, mask) (dst) = ((dst) & ~(mask)) | ((value) & mask)
#endif

#ifndef getLowByte
#define getLowByte(x) 				((x) & 0xFF)
#endif
#ifndef getHighByte
#define getHighByte(x) 				(((x) >> 8) & 0xFF)
#endif
#ifndef getByteN
#define getByteN(x, n) 				(((x) >> ((n) << 3)) & 0xFF)
#endif


//#endif // ifdef constexpr

#endif /* UTIL_BITFIELD_H_ */
