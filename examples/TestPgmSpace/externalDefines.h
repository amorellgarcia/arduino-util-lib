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

#ifndef EXTERNAL_DEFINES_H__
#define EXTERNAL_DEFINES_H__

#include "util/pgm_space.h"


typedef struct {
	char a;
	int b;
	char c;
} myStruct_t;


PGMSPACE_EXTERN(int, exMyInt);
extern size_t exMyArraySize;
PGMSPACE_EXTERN_ARRAY(int, exMyArray);

PGMSPACE_EXTERN_STRING(exMyStr);

PGMSPACE_EXTERN_ARRAY(int, exMyArray2);
extern size_t exMyArray2Size;

PGMSPACE_EXTERN_STRING(exMyStr1);
PGMSPACE_EXTERN_STRING(exMyStr2);
PGMSPACE_EXTERN_STRING(exMyStr3);

PGMSPACE_EXTERN_ARRAY(PgmSpaceString, exMyStrArray);
extern size_t exMyStrArraySize;

PGMSPACE_EXTERN_STRUCT(myStruct_t, exMyStruct);


namespace Syntax { namespace Basic {
	struct type_t;
}}

extern const Syntax::Basic::type_t &AT;


#endif // EXTERNAL_DEFINES_H__
