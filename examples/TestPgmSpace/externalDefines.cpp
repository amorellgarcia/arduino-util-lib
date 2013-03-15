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

#include <util/pgm_space.h>
#include "externalDefines.h"

PGMSPACE(int, exMyInt, 10);
PGMSPACE_ARRAY(int, exMyArray, 0, 1, 2, 3, 4, 5, 6);
size_t exMyArraySize = PGMSPACE_ARRAY_SIZE(exMyArray);

PGMSPACE_STRING(exMyStr, "hello");

PGMSPACE_ARRAY_BEGIN(int, exMyArray2)
	7, 8, 9, 10, 11, 12, 13, 14
PGMSPACE_ARRAY_END(int, exMyArray2)
size_t exMyArray2Size = PGMSPACE_ARRAY_SIZE(exMyArray2);

PGMSPACE_STRING(exMyStr1, "hello1");
PGMSPACE_STRING(exMyStr2, "hello2");
PGMSPACE_STRING(exMyStr3, "hello3");

PGMSPACE_ARRAY_BEGIN(PgmSpaceString, exMyStrArray)
	PGMSPACE_REF_STRING(exMyStr1),
	PGMSPACE_REF_STRING(exMyStr2),
	PGMSPACE_REF_STRING(exMyStr3),
PGMSPACE_ARRAY_END(PgmSpaceString, exMyStrArray)
size_t exMyStrArraySize = PGMSPACE_ARRAY_SIZE(exMyStrArray);

PGMSPACE_STRUCT(myStruct_t, exMyStruct, '[', 10, ']');
