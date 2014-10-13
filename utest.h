/* Unit Testing Include File */


#ifndef _UTEST_H
#define _UTEST_H

/* Includes and Externs **************/



/* Private Defines, Typedefs, Enumerations, and Structures **/

#define UTEST_INVALID_DATA	0xDEAD
#define UTEST_RESULT_FAIL	0
#define UTEST_RESULT_PASS	1

typedef struct tUTestSet
{
	char*			description;
	void			(*beforeAll)(void);
	void 			(*beforeEach)(void);
	unsigned int	numCases;
	unsigned int	firstCase;
} UTestSet_t;

typedef struct tUTestCase
{
	unsigned int	whichSet;
	char*			description;
	void			(*test)(void);
	unsigned int	passFail;
} UTestCase_t;




/* Private Macros ********************/

/**
	This function is used to build a set of test cases.
	Two accompanying functions may be specified: one to run at the start of the set
	and another to run before each test case in the set. It has no return value.
	@param [in] fut This is a pointer to the function under test
	@param [in] beforeall This is a pointer to the function to run at the start of the test set
	@param [in] beforeeach This is a pointer to the function to run at the start of each test case
*/
#define UTEST_add_testset(fut,beforeall,beforeeach) utest_add_testset(#fut,beforeall,beforeeach)

/**
	This function is used to add a test case to the last test set created.
	The function containing the activities of the test case may be specified.
	It has no return value.
	@param [in] testfn This is a pointer to the function containing the test case activities
*/
#define UTEST_add_testcase(testfn) utest_add_testcase(#testfn,testfn)

/**
	This function may be used to run a single test case. Only the before-each
	function of the parent test set will be run. It has no return value.
	@param [in] testcase The overall index of the test case to perform
*/
#define UTEST_perform_case(testcase) utest_perform_case(testcase)

/**
	This function may be used to run a single test set. It has no return value.
	@param [in] testset The index of the test set to perform
*/
#define UTEST_perform_set(testset) utest_perform_set(testset)

/**
	This function executes all the test sets and their consituent test cases.
	It has no parameter or return value.
*/
#define UTEST_perform_all() utest_perform_all()

/**
	This function outputs a reference number that may be associated with the subsequent
	test assertion. This function is used in building test cases or prequel functions.
	It has no return value.
	@param [in] x The numeric requirement reference to output
*/
#define UTEST_ref(x) utest_ref(x)

/**
	This function assigns a variable value and documents the action. This function
	is used in building test cases or prequel functions. It has no return value.
	@param [in] var The variable to set
	@param [in] val The value to which the variable is set
*/
#define UTEST_let(var,val) { var = val; utest_let(#var,#val,val); }

/**
	This function calls the actual function under test and documents the action.
	Any return value from the function is maintained for assertions. The function
	execution is also timed and this time is maintained for assertions. This
	function is used in building test cases or prequel functions.It has no
	return value.
	@param [in] fn This is a pointer to the function under test
	@param [in] ... A variable-length list of any parameters that the function under test takes
*/
#define UTEST_call(fn,...) { utest_precall(#fn); utest_postcall((long)fn(__VA_ARGS__)); }

/**
	This function tests and documents an equal assertion. It has no return value. Falseness
	of the assertion will cause the present test case to fail.
	@param [in] var The variable to test
	@param [in] exp The expected value to test against
*/
#define UTEST_assert(var,exp) utest_assert(#var,#exp,var,exp)

/**
	This function tests and documents a not-equal assertion. It has no return value. Falseness
	of the assertion will cause the present test case to fail.
	@param [in] var The variable to test
	@param [in] exp The expected value to test against
*/
#define UTEST_assert_not_equal(var,exp) utest_assert(#var,#exp,var,exp)

/**
	This function tests and documents the assertion that the variable < expected value.
	It has no return value. Falseness of the assertion will cause the present test case to fail.
	@param [in] var The variable to test
	@param [in] exp The expected value to test against
*/
#define UTEST_assert_less(var,exp) utest_assert(#var,#exp,var,exp)

/**
	This function tests and documents the assertion that the variable > expected value.
	It has no return value. Falseness of the assertion will cause the present test case to fail.
	@param [in] var The variable to test
	@param [in] exp The expected value to test against
*/
#define UTEST_assert_more(var,exp) utest_assert(#var,#exp,var,exp)

/**
	This function tests and documents the assertion that the variable is between the two values.
	It has no return value. Falseness of the assertion will cause the present test case to fail.
	@param [in] var The variable to test
	@param [in] min The lower-range value to test against
	@param [in] max The upper-range value to test against
*/
#define UTEST_assert_between(var,min,max) utest_assert(#var,#min,#max,var,min,max)

/**
	This function tests and documents an equal assertion against the return value of the function
	under test. It has no return value. Falseness of the assertion will cause the present test case to fail.
	@param [in] exp The expected value to test against
*/
#define UTEST_assert_return(exp) utest_assert_return(#exp,exp)

/**
	This function tests and documents the assertion that the execution time of the function
	under test is a certain expected time within a certain tolerance. It has no return value.
	Falseness of the assertion will cause the present test case to fail.
	@param [in] x The expected execution time of the FUT in microseconds (us)
	@param [in] tol The +/- tolerance of the expected value in microseconds (us)
*/
#define UTEST_assert_time(x,tol) utest_assert_time(x,tol)

/**
	This function tests and documents the assertion that the execution time of the function
	under test takes longer than a certain expected time. It has no return value.
	Falseness of the assertion will cause the present test case to fail.
	@param [in] x The minimum expected execution time of the FUT in microseconds (us)
*/
#define UTEST_assert_time_exceeds(x) utest_assert_time_exceeds(x)

/**
	This function tests and documents the assertion that the execution time of the function
	under test takes less time than a certain expected time. It has no return value.
	Falseness of the assertion will cause the present test case to fail.
	@param [in] x The maximum expected execution time of the FUT in microseconds (us)
*/
#define UTEST_assert_time_beats(x) utest_assert_time_beats(x)

/**
	This function causes the specified subroutine to be flagged as having been called.
	This function is used in stubbed out dependencies to log control flow to be used
	for subsequent assertions.
	@param [in] x This is a pointer to the subroutine to be counted
*/
#define UTEST_count_calls(x) utest_count_calls((int*)x)

/**
	This function tests and documents the assertion that the specified subroutine was
	called by the FUT. It has no return value. 	Falseness of the assertion will cause
	the present test case to fail.
	@param [in] x This is a pointer to the subroutine to be checked for execution
*/
#define UTEST_assert_called(x) utest_assert_called(#x,(int*)x)

/**
	This function documents the accumulated results of all test set and their constituent
	test cases. It has no parameters or return value.
*/	
#define UTEST_summary() utest_summary()

/**
	This function document the execution time of the preceeding FUT. It has no parameters or
	return value.
*/
#define UTEST_benchmark() utest_benchmark()


/**
	This function is used as a placeholder for unneeded before-all and before-each
	testset parameters. It takes no parameters and has no return value.
*/
#define UTEST_no_action utest_no_action

/**
	This function must be called before any tests are configured or run.
	It takes care of platform and test variable initialization. It takes
	no parameters and has no return value.
*/
#define UTEST_init() utest_init()

/**
	This function is the put string function that outputs the given
	null-terminated string to the standard test output. It has no return value.
	@param [in] str A pointer to a null-terminated character array
*/
#define UTEST_puts(str) utest_puts(str);



extern void utest_add_testset(char* fut,void (*beforeall)(void), void (*beforeeach)(void));
extern void utest_add_testcase(char* testname, void (*testfn)(void));
extern void utest_perform_case(unsigned int testcase);
extern void utest_perform_set(unsigned int testset);
extern void utest_perform_all(void);
extern void utest_ref(unsigned int x);
extern void utest_let(char* varname, char* valname, unsigned long val);
extern void utest_precall(char* fn);
extern void utest_postcall(long ret);
extern void utest_assert(char* varname, char* expname, long var, long exp);
extern void utest_assert_not_equal(char* varname, char* expname, long var, long exp);
extern void utest_assert_less(char* varname, char* expname, long var, long exp);
extern void utest_assert_more(char* varname, char* expname, long var, long exp);
extern void utest_assert_between(char* varname, char* minname, char* maxname, long var, long min, long max);
extern void utest_assert_return(char* expname, long exp);
extern void utest_assert_time(unsigned long x, unsigned long tol);
extern void utest_assert_time_exceeds(unsigned long x);
extern void utest_assert_time_beats(unsigned long x);
extern void utest_count_calls(int* x);
extern void utest_assert_called(char* fname, int* fp);
extern void utest_benchmark(void);
extern void utest_summary(void);

extern void utest_no_action (void);
extern void utest_init (void);
extern void utest_puts(char* buf);


#endif

