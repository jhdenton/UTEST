/* Unit Testing Core File */


/* Includes and Externs **************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utest.h"
#include "utest_config.h"


/* Private Variable Definitions ******/

unsigned int utestResult;
unsigned int utestPassCount;
unsigned long utestTimestamp0, utestTimestamp1;
long utestRetval, utestTemp;
char utestBuf[UTEST_CONFIG_STRING_BUFFER_SIZE];

unsigned int utestCaseI, utestSetI, utestI;
unsigned int utestNumSets, utestNumCases;
unsigned int utestCallCount;
int* utestCalls[UTEST_CONFIG_MAX_NUM_SUB_CALLS];
UTestSet_t utestSet[UTEST_CONFIG_MAX_NUM_TEST_SETS];
UTestCase_t utestCase[UTEST_CONFIG_MAX_NUM_TEST_CASES];

unsigned char utestVerbose = U_TRUE;

/* Public Methods ********************/

void utest_set_utestVerbose(unsigned char set)
{
	utestVerbose = set;
}

void utest_add_testset(char* fut,void (*beforeall)(void), void (*beforeeach)(void))
{
	utestSet[utestNumSets].description = fut;
	utestSet[utestNumSets].beforeAll = beforeall;
	utestSet[utestNumSets].beforeEach = beforeeach;
	utestSet[utestNumSets].firstCase = utestNumCases;
	utestNumSets += 1;
}


void utest_add_testcase(char* testname, void (*testfn)(void))
{
	utestCase[utestNumCases].whichSet = utestNumSets-1;
	utestCase[utestNumCases].description = testname;
	utestCase[utestNumCases].test = testfn;
	utestCase[utestNumCases].passFail = UTEST_RESULT_FAIL;
	utestNumCases += 1;
	utestSet[utestNumSets-1].numCases += 1;
}


void utest_perform_case(unsigned int testcase)
{
	sprintf(utestBuf,"\r\n  Test Case %d-%d: %s\r\n", utestCase[testcase].whichSet+1, testcase-utestSet[utestCase[testcase].whichSet].firstCase+1, utestCase[testcase].description);
	if(utestVerbose) utest_puts(utestBuf);
	utestCallCount = 0;
	utestResult = UTEST_RESULT_PASS;
	(*utestSet[utestCase[testcase].whichSet].beforeEach)();
	(*utestCase[testcase].test)();
	utestCase[testcase].passFail = utestResult;
	if (utestResult==UTEST_RESULT_PASS) utestPassCount++;
	sprintf(utestBuf,"\r\n  Result: %s\r\n\n",(utestResult==UTEST_RESULT_PASS)?"_PASS_":"_FAIL_");
	utest_puts(utestBuf);
}


void utest_perform_set(unsigned int testset)
{
	sprintf(utestBuf,"\r\n\n\nTest Set %d: %s\r\n", testset+1, utestSet[testset].description);
	if(utestVerbose) utest_puts(utestBuf);
	utestPassCount = 0;
	(*utestSet[testset].beforeAll)();
	for (utestCaseI = utestSet[testset].firstCase; utestCaseI < (utestSet[testset].firstCase + utestSet[testset].numCases); utestCaseI++)
	{
		utest_perform_case(utestCaseI);
	}
	sprintf(utestBuf,"\r\n\nTest Set Results: % 2d of % 2d test cases passed: %d%%\r\n", utestPassCount, utestSet[testset].numCases, (utestPassCount*100)/utestSet[testset].numCases);
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_perform_all(void)
{
	for (utestSetI = 0; utestSetI < utestNumSets; utestSetI++)
	{
		utest_perform_set(utestSetI);
	}
}


void utest_ref(char* x)
{
	sprintf(utestBuf,"\r\n    Reference: %s\r\n", x);
	utest_puts(utestBuf);
}


void utest_rem(char* x)
{
	sprintf(utestBuf,"\r\n    %s\r\n", x);
	utest_puts(utestBuf);
}


void utest_let(char* varname, char* valname, unsigned long val)
{
	sprintf(utestBuf,"      > Let %s = %s (%ld)\r\n", varname, valname, (long)val);
	if(utestVerbose) utest_puts(utestBuf); 
}


void utest_precall(char* fn)
{
	sprintf(utestBuf, "        + Calling UUT %s...\r\n", fn);
	if(utestVerbose) utest_puts(utestBuf);
	utestRetval = UTEST_INVALID_DATA;
	utestTimestamp0 = clock();
}


void utest_postfunc(long ret)
{
	utestRetval = ret;
	utestTimestamp1 = clock();
	sprintf(utestBuf, "        - Returned from UUT.\r\n");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_postsub(void)
{
	utestTimestamp1 = clock();
	sprintf(utestBuf, "        - Returned from UUT.\r\n");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert(char* varname, char* expname, long var, long exp)
{
	if(var != exp) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < %s should be %s (%ld), is %ld: %s\r\n", varname, expname, exp, var, (var == exp) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_not_equal(char* varname, char* expname, long var, long exp)
{
	if(var == exp) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < %s should not be %s (%ld), is %ld: %s\r\n", varname, expname, exp, var, (var != exp) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_less(char* varname, char* expname, long var, long exp)
{
	if(var >= exp) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < %s should be less than %s (%ld), is %ld: %s\r\n", varname, expname, exp, var, (var < exp) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_more(char* varname, char* expname, long var, long exp)
{
	if(var <= exp) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < %s should be less than %s (%ld), is %ld: %s\r\n", varname, expname, exp, var, (var > exp) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_between(char* varname, char* minname, char* maxname, long var, long min, long max)
{
	if((var < min) || (var > max)) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < %s should be between %s (%ld) and %s (%ld), is %ld: %s\r\n", varname, minname, min, maxname, max, var, ((var >= min) && (var <= max)) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_string_equal(char* varname, char* var, char *exp)
{
    utestTemp = strcmp(var, exp);
    if(0 != utestTemp) utestResult = UTEST_RESULT_FAIL;
    sprintf(utestBuf, "      < %s should be %s, is %s: %s\r\n", varname, exp, var, (utestTemp==0) ? "PASS" : "FAIL");
    if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_return(char* expname, long exp)
{
	if(utestRetval != exp) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < Returned value should be %s (%ld), is %ld: %s\r\n", expname, exp, utestRetval, (utestRetval == exp) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf); 
}


void utest_assert_time(unsigned long x, unsigned long tol)
{
	utestTemp = 1;
	if ((utestTimestamp1 - utestTimestamp0) > ((unsigned long)(x + tol) * UTEST_CONFIG_CLOCKS_PER_USEC)) utestTemp = 0;
	if ((utestTimestamp1 - utestTimestamp0) < ((unsigned long)(x - tol) * UTEST_CONFIG_CLOCKS_PER_USEC)) utestTemp = 0;
	sprintf(utestBuf,"      < Time should have been %ldus +/- %ldus, was %luus: %s\r\n", x, tol, (utestTimestamp1 - utestTimestamp0) / UTEST_CONFIG_CLOCKS_PER_USEC, (utestTemp == 1) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
	if (utestTemp == 0) utestResult = UTEST_RESULT_FAIL;
}


void utest_assert_time_exceeds(unsigned long x)
{
	utestTemp = 1;
	if ((utestTimestamp1 - utestTimestamp0) < (x * UTEST_CONFIG_CLOCKS_PER_USEC)) utestTemp = 0;
	sprintf(utestBuf,"      < Time should have been %ldus or more, was %luus: %s\r\n", x, (utestTimestamp1 - utestTimestamp0) / UTEST_CONFIG_CLOCKS_PER_USEC, (utestTemp == 1) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
	if (utestTemp == 0) utestResult = UTEST_RESULT_FAIL;
}


void utest_assert_time_beats(unsigned long x)
{
	utestTemp = 1;
	if ((utestTimestamp1 - utestTimestamp0) > (x * UTEST_CONFIG_CLOCKS_PER_USEC)) utestTemp = 0;
	sprintf(utestBuf,"      < Time should have been %ldus or less, was %luus: %s\r\n", x, (utestTimestamp1 - utestTimestamp0) / UTEST_CONFIG_CLOCKS_PER_USEC, (utestTemp == 1) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
	if (utestTemp == 0) utestResult = UTEST_RESULT_FAIL;
}


void utest_count_calls(int* fp)
{
	utestCalls[utestCallCount] = fp;
	utestCallCount++;
}


void utest_assert_called(char* fname, int* fp)
{
	utestTemp = 0;
	for (utestI = 0; utestI < utestCallCount; utestI++)
	{
		if (utestCalls[utestI] == fp) utestTemp = 1;
	}
	if (utestTemp == 0) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < Should have run %s: %s\r\n", fname, (utestTemp == 1) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_not_called(char* fname, int* fp)
{
	utestTemp = 0;
	for (utestI = 0; utestI < utestCallCount; utestI++)
	{
		if (utestCalls[utestI] == fp) utestTemp = 1;
	}
	if (utestTemp == 1) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < Should not have run %s: %s\r\n", fname, (utestTemp == 0) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_assert_called_n(char* fname, int* fp, int n)
{
	utestTemp = 0;
	int count_temp = 0;
	if( n == 0) utestTemp = 1; /* Allow for n=0, which would not exist in call list */
	for (utestI = 0; utestI < utestCallCount; utestI++)
	{
		if ((utestCalls[utestI] == fp))
		{
			count_temp ++;
			if(count_temp == n)
			{
				utestTemp = 1;	
			}
			else
			{
				utestTemp = 0;
			}
		}
	}

	if (utestTemp == 0) utestResult = UTEST_RESULT_FAIL;
	sprintf(utestBuf, "      < Should have run %s %d times, was (%d) times: %s\r\n", fname,n, count_temp, (utestTemp == 1) ? "PASS" : "FAIL");
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_benchmark(void)
{
	sprintf(utestBuf, "        @ Benchmark time of UUT: %luus\r\n", (utestTimestamp1 - utestTimestamp0) / UTEST_CONFIG_CLOCKS_PER_USEC);
	if(utestVerbose) utest_puts(utestBuf);
}


void utest_summary(void)
{
	unsigned int total, pass, gtotal, gpass;
	gtotal = 0;
	gpass = 0;
	utest_puts("\r\n\n\nSet  Pass  Fail\r\n");
	for (utestSetI = 0; utestSetI < utestNumSets; utestSetI++)
	{
		total = utestSet[utestSetI].numCases;
		pass = 0;
		for (utestCaseI = utestSet[utestSetI].firstCase; utestCaseI < (utestSet[utestSetI].firstCase + total); utestCaseI++)
		{
			if (utestCase[utestCaseI].passFail == UTEST_RESULT_PASS) pass++;
		}
		sprintf(utestBuf, " % 2d   % 3d   % 3d    %d%%\r\n", utestSetI+1, pass, total-pass, (100*pass)/total);
        utest_puts(utestBuf);
		gtotal += total;
		gpass += pass;
	}
	sprintf(utestBuf, "------------------------\r\nTotal % 3d   % 3d    %d%%\r\n", gpass, gtotal-gpass, (gpass*100)/gtotal);
    utest_puts(utestBuf);
}


void UTEST_no_action (void)
{
	return;
}

