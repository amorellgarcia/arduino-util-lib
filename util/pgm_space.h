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

#ifndef UTIL_PGM_SPACE_H_
#define UTIL_PGM_SPACE_H_


#include <avr/pgmspace.h>
#include <Print.h>


/**
 * Struct that represents a value in program space.
 */
template<typename T, size_t TSize = sizeof(T)>
struct PgmSpace {
	/**
	 * Returns the native pointer. This pointer must be used with special
	 * AVR functions which name ends with _P, strlen_P, etc.
	 *
	 * @return pointer to native type.
	 */
	inline const T *cast() const {
		return reinterpret_cast<const T *>(this);
	}

	/**
	 * Copies this structure value to the memory pointed by @a dst.
	 *
	 * @param dst reference to memory structure where to copy.
	 */
	inline void read(T &dst) const {
		memcpy_P(&dst, this, sizeof(T));
	}

	/**
	 * Implicit convert operator to native type. This allows using this
	 * structure as you would use the native type.
	 */
	inline operator T() const {
		T aux;
		memcpy_P(&aux, this, sizeof(T));
		return aux;
	}

	/**
	 * Stub data that tells compiler which size has native structure so pointers
	 * to this struct can be converted to native structure pointers.
	 */
	const T __data_hack;
};

template<typename T>
struct PgmSpace<T, 1> {
	inline const T *cast() const {
		return reinterpret_cast<const T *>(this);
	}

	inline void read(T &dst) const {
		dst = (T)pgm_read_byte(this);
	}

	inline operator T() const {
		return (T)pgm_read_byte(this);
	}

	const T __data_hack;
};

template<typename T>
struct PgmSpace<T, 2> {
	inline const T *cast() const {
		return reinterpret_cast<const T *>(this);
	}

	inline void read(T &dst) const {
		memcpy_P(&dst, this, 2);
	}

	inline operator T() const {
		return (T)pgm_read_word(this);
	}

	const T __data_hack;
};

template<typename T>
struct PgmSpace<T, 4> {
	inline const T *cast() const {
		return reinterpret_cast<const T *>(this);
	}

	inline void read(T &dst) const {
		memcpy_P(&dst, this, 4);
	}

	inline operator T() const {
		return (T)pgm_read_dword(this);
	}

	const T __data_hack;
};

class __FlashStringHelper;
/**
 * Use default Android class for program strings to allow using previous
 * functions in @a Print, @a String, etc
 */
typedef const __FlashStringHelper * PgmSpaceString;

template<typename T, size_t TSize>
inline Print &operator <<(Print &p, const PgmSpace<T, TSize> &value) {
	return (p << value.operator T());
}

template<typename T, size_t TSize>
inline Print &operator <<(Print &p, const PgmSpace<T, TSize> *value) {
	return (p << value->operator T());
}

inline Print &operator <<(Print &p, const PgmSpaceString value) {
	p.print(value);
	return p;
}


#define _PGMSPACE_NAME(x)				x##__pgmspace

#define _PGMSPACE_DECL(type, x)        const type  _PGMSPACE_NAME(x)
#define _PGMSPACE_DECL_STRUCT(type, x) const type  _PGMSPACE_NAME(x)
#define _PGMSPACE_DECL_ARRAY(type, x)  const type  _PGMSPACE_NAME(x)[]
#define _PGMSPACE_DECL_STRING(x)       const char _PGMSPACE_NAME(x)[]

#define _PGMSPACE_VAR(type, x)         const PgmSpace<type> &x
#define _PGMSPACE_VAR_STRUCT(type, x)  const PgmSpace<type> &x
#define _PGMSPACE_VAR_ARRAY(type, x)   const PgmSpace<type> * const x
#define _PGMSPACE_VAR_STRING(x)        const PgmSpaceString x


#define PGMSPACE_REF(type, x)         reinterpret_cast<_PGMSPACE_VAR(type,)>(_PGMSPACE_NAME(x))
#define PGMSPACE_REF_STRUCT(type, x)  reinterpret_cast<_PGMSPACE_VAR_STRUCT(type,)>(_PGMSPACE_NAME(x))
#define PGMSPACE_REF_ARRAY(type, x)   reinterpret_cast<_PGMSPACE_VAR_ARRAY(type,)>(_PGMSPACE_NAME(x))
#define PGMSPACE_REF_STRING(x)        reinterpret_cast<_PGMSPACE_VAR_STRING()>(_PGMSPACE_NAME(x))


#define PGMSPACE_INLINE(type, value) \
	reinterpret_cast<_PGMSPACE_REF(type,)>((__extension__({static _PGMSPACE_DECL(type, __c) PROGMEM = (value); __c;})))

#define PGMSPACE_INLINE_STRUCT(type, ...) \
	reinterpret_cast<_PGMSPACE_REF_STRUCT(type,)>((__extension__({static _PGMSPACE_DECL_STRUCT(type, __c) PROGMEM = {__VA_ARGS__}; __c;})))

#define PGMSPACE_INLINE_ARRAY(type, ...) \
	reinterpret_cast<_PGMSPACE_REF_ARRAY(type,)>((__extension__({static _PGMSPACE_DECL_ARRAY(type, __c) PROGMEM = {__VA_ARGS__}; __c;})))

#define PGMSPACE_INLINE_STRING(text) \
	reinterpret_cast<_PGMSPACE_REF_STRING()>((__extension__({static _PGMSPACE_DECL_STRING(__c) PROGMEM = (text); __c;})))


#define PGMSPACE(type, x, value) \
	static _PGMSPACE_DECL(type, x) PROGMEM = (value); \
	_PGMSPACE_VAR(type, x) = PGMSPACE_REF(type, x)

#define PGMSPACE_STRUCT(type, x, ...) \
	static _PGMSPACE_DECL_STRUCT(type, x) PROGMEM = {__VA_ARGS__}; \
	_PGMSPACE_VAR_STRUCT(type, x) = PGMSPACE_REF_STRUCT(type, x)

#define PGMSPACE_ARRAY(type, x, ...) \
	static _PGMSPACE_DECL_ARRAY(type, x) PROGMEM = {__VA_ARGS__}; \
	_PGMSPACE_VAR_ARRAY(type, x) = PGMSPACE_REF_ARRAY(type, x)

#define PGMSPACE_STRING(x, text) \
	_PGMSPACE_DECL_STRING(x) PROGMEM = text; \
	_PGMSPACE_VAR_STRING(x) = PGMSPACE_REF_STRING(x)

#define PGMSPACE_STRING_NULL(x) \
	_PGMSPACE_VAR_STRING(x) = NULL

#define PGMSPACE_STRUCT_BEGIN(type, x) \
	static _PGMSPACE_DECL_STRUCT(type, x) PROGMEM = {

#define PGMSPACE_STRUCT_END(type, x) \
	}; _PGMSPACE_VAR_STRUCT(type, x) = PGMSPACE_REF_STRUCT(type, x);

#define PGMSPACE_ARRAY_BEGIN(type, x) \
	static _PGMSPACE_DECL_ARRAY(type, x) PROGMEM = {

#define PGMSPACE_ARRAY_END(type, x) \
	}; _PGMSPACE_VAR_ARRAY(type, x) = PGMSPACE_REF_ARRAY(type, x);

#define PGMSPACE_ARRAY_SIZE(x) \
		(sizeof(_PGMSPACE_NAME(x)) / sizeof(_PGMSPACE_NAME(x)[0]))


#define PGMSPACE_EXTERN(type, x) \
	extern _PGMSPACE_VAR(type, x)

#define PGMSPACE_EXTERN_STRUCT(type, x) \
	extern _PGMSPACE_VAR_STRUCT(type, x)

#define PGMSPACE_EXTERN_ARRAY(type, x) \
	extern _PGMSPACE_VAR_ARRAY(type, x)

#define PGMSPACE_EXTERN_STRING(x) \
	extern _PGMSPACE_VAR_STRING(x)

#endif /* UTIL_PGM_SPACE_H_ */
