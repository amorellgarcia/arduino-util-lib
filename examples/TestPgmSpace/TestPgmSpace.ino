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

#include <UtilLib.h>
#include <Streaming.h>
#include "util/pgm_space.h"
#include "externalDefines.h"


PGMSPACE(int, myInt, 10);
PGMSPACE_ARRAY(int, myArray, 0, 1, 2, 3, 4, 5, 6);
PGMSPACE_STRING(myStr, "hello");

PGMSPACE_ARRAY_BEGIN(int, myArray2)
	7, 8, 9, 10, 11, 12, 13, 14
PGMSPACE_ARRAY_END(int, myArray2)

PGMSPACE_STRING(myStr1, "hello1");
PGMSPACE_STRING(myStr2, "hello2");
PGMSPACE_STRING(myStr3, "hello3");

PGMSPACE_ARRAY_BEGIN(PgmSpaceString, myStrArray)
	myStr1,
	myStr2,
	myStr3
PGMSPACE_ARRAY_END(PgmSpaceString, myStrArray)


PGMSPACE_STRUCT(myStruct_t, myStruct, '[', 10, ']');

template <typename T>
void showArray(const PgmSpace<T> *myArray, size_t N) {
	Serial.print(F("Read array("));
	Serial.print(N);
	Serial.print(F("): "));
	if (N > 0) {
		Serial.print(myArray[0]);
		for(size_t i = 1; i < N; ++i) {
			Serial.print(F(", "));
			Serial.print(myArray[i]);
		}
		Serial.println();
	}
}

template <typename T, size_t length>
void showArray(const PgmSpace<T> myArray[length]) {
	showArray(myArray, length);
}


void testGlobal() {
	Serial.print(F("Read int: "));
	Serial.println(myInt);

	showArray(myArray, PGMSPACE_ARRAY_SIZE(myArray));
	showArray(myArray2, PGMSPACE_ARRAY_SIZE(myArray2));

	Serial.print(F("Read string: "));
	Serial.println(myStr);

	Serial.print(F("Read string1: "));
	Serial.println((const __FlashStringHelper *)_PGMSPACE_NAME(myStr1));
	Serial.print(F("Read string2: "));
	Serial.println((const __FlashStringHelper *)_PGMSPACE_NAME(myStr2));
	Serial.print(F("Read string3: "));
	Serial.println((const __FlashStringHelper *)_PGMSPACE_NAME(myStr3));

	showArray(myStrArray, PGMSPACE_ARRAY_SIZE(myStrArray));

	Serial.print(F("Read structure: "));
	myStruct_t aux;
	myStruct.read(aux);
	Serial.print(F(".a="));
	Serial.print(aux.a);
	Serial.print(F(", .b="));
	Serial.print(aux.b);
	Serial.print(F(", .c="));
	Serial.println(aux.c);
}

void testExtern() {
	Serial.print(F("Read int: "));
	Serial.println(exMyInt);

	showArray(exMyArray, exMyArraySize);
	showArray(exMyArray2, exMyArray2Size);

	Serial.print(F("Read string: "));
	Serial.println(exMyStr);

	Serial.print(F("Read string1: "));
	Serial.println(exMyStr1);
	Serial.print(F("Read string2: "));
	Serial.println(exMyStr2);
	Serial.print(F("Read string3: "));
	Serial.println(exMyStr3);

	showArray(exMyStrArray, exMyStrArraySize);

	Serial.print(F("Read structure: "));
	myStruct_t aux;
	exMyStruct.read(aux);
	Serial.print(F(".a="));
	Serial.print(aux.a);
	Serial.print(F(", .b="));
	Serial.print(aux.b);
	Serial.print(F(", .c="));
	Serial.println(aux.c);
}

void setup() {
	Serial.begin(9600);

	testGlobal();
	testExtern();
}

void loop() {

}
