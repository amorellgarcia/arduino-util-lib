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

#ifndef UTIL_TIME_H_
#define UTIL_TIME_H_


namespace util {

/**
 * Returns true if a timer count overflowed.
 * Currently is a simple @code before > after @endcode comparison. This should
 * be sufficient, as Arduino time overflows each 51 days.
 *
 * @param before previous time value
 * @param after current time value
 * @return true if overflow occurred, false otherwise.
 */
extern bool isTimeOverflow(const unsigned long &before, const unsigned long &after);

/**
 * Returns elapsed time between @a before and @a after but taken care if an
 * overflow has occurred.
 *
 * @param before previous time value.
 * @param after current time value.
 * @return time difference between @a before and @a after
 */
extern unsigned long elapsedTime(const unsigned long &before, const unsigned long &after);

/**
 * Checks if a @a timeoutMs time has elapsed since @a start. It takes care for
 * overflow conditions.
 *
 * @param start time where interval started.
 * @param timeoutMs timeout value
 * @return true if a minimum of @a timeoutMs time has elapsed since @a start,
 * false otherwise.
 */
extern bool timedOut(const unsigned long &start, const unsigned int &timeoutMs);

} // namespace util


#endif /* UTIL_TIME_H_ */
