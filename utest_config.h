/* Unit Testing Configuration File */

#ifndef _UTEST_CONFIG_H
#define _UTEST_CONFIG_H


/* ADD PLATFORM PORT INCLUDES HERE */
#include "p33FJ128GP804.h"
/* ADD PLATFORM PORT INCLUDES HERE */


/** This is the maximum allowed size for any single string sent via the utest_puts() function. */
#define UTEST_CONFIG_STRING_BUFFER_SIZE		256

/** This is the maximum allowed number of test sets. */
#define UTEST_CONFIG_MAX_NUM_TEST_SETS		50

/** This is the maximum allowed total number of test cases (they may be distributed through the individual test sets in any numbers). */
#define UTEST_CONFIG_MAX_NUM_TEST_CASES		200

/** This is the maximum allowed number of subroutines that may be called by the unit under test within any single test case. */
#define UTEST_CONFIG_MAX_NUM_SUB_CALLS		100

/** This is the platform-specific number of clock ticks returned by the time.h clock() function. */
#define UTEST_CONFIG_CLOCKS_PER_USEC		10


#endif
