/* main entry point and test definitions for low-level testing */

#include "utest_core.c"
#include "utest_port.c"


/* INCLUDE THE MODULE UNDER TEST HERE */
#include "module.c"
/* INCLUDE THE MODULE UNDER TEST HERE */


/* PLACE THE HOOKS FOR DEPENDENCIES HERE */
int barParam, barReturn;
int bar(int param)
{
	barParam = param;
	return(barReturn);
}
/* PLACE THE HOOKS FOR DEPENDENCIES HERE */


/* TEST_CODE HERE */
#define MAX_PARAM	0x7FFE
int p1, p2;
void test_foo_before_each()
{
    UTEST_let(barParam, UTEST_INVALID_DATA);
}

void test_foo_max_param2_param1_equal()
{
    UTEST_let(p1,MAX_PARAM/2);
    UTEST_let(p2,MAX_PARAM);
	UTEST_let(barReturn, MAX_PARAM/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, MAX_PARAM);
	UTEST_ref(102);
	UTEST_assert_return(p1);
}

void test_foo_max_param2_param1_greater()
{
    UTEST_let(p1,MAX_PARAM/2+1);
    UTEST_let(p2,MAX_PARAM);
	UTEST_let(barReturn, p2/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, MAX_PARAM);
	UTEST_ref(102);
	UTEST_assert_return(p1);
}

void test_foo_max_param2_param2_out()
{
    UTEST_let(p1,MAX_PARAM/2-1);
    UTEST_let(p2,MAX_PARAM);
	UTEST_let(barReturn, p2/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, MAX_PARAM);
	UTEST_ref(101);
	UTEST_assert_return(p2);
}

void test_foo_min_param1_param1_equal()
{
    UTEST_let(p1,1);
    UTEST_let(p2,2);
	UTEST_let(barReturn, p2/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, 2);
	UTEST_ref(102);
	UTEST_assert_return(p1);
}

void test_foo_min_param1_param1_greater()
{
    UTEST_let(p1,1);
    UTEST_let(p2,1);
	UTEST_let(barReturn, p2/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, 1);
	UTEST_ref(102);
	UTEST_assert_return(p1);
}

void test_foo_min_param1_param2_out()
{
    UTEST_let(p1,1);
    UTEST_let(p2,4);
	UTEST_let(barReturn, p2/2);
	UTEST_call(foo, p1, p2);
	UTEST_assert(barParam, 4);
	UTEST_ref(101);
	UTEST_assert_return(p2);
}

void test_foo_neg_param1()
{
    UTEST_let(p1,-1);
    UTEST_let(p2,100);
	UTEST_let(barReturn, UTEST_INVALID_DATA);
	UTEST_call(foo, p1, p2);
	UTEST_ref(103);
	UTEST_assert_return(0);
}

void test_foo_neg_param2()
{
    UTEST_let(p1,100);
    UTEST_let(p2,-1);
	UTEST_let(barReturn, UTEST_INVALID_DATA);
	UTEST_call(foo, p1, p2);
	UTEST_ref(103);
	UTEST_assert_return(0);
}

void test_foo_neg_params()
{
    UTEST_let(p1,-1);
    UTEST_let(p2,-1);
	UTEST_let(barReturn, UTEST_INVALID_DATA);
	UTEST_call(foo, p1, p2);
	UTEST_ref(103);
	UTEST_assert_return(0);
}
/* TEST_CODE HERE */


int main (void)
{
	UTEST_init();

	UTEST_add_testset(foo,UTEST_no_action,test_foo_before_each);
	UTEST_add_testcase(test_foo_max_param2_param1_equal);
	UTEST_add_testcase(test_foo_max_param2_param1_greater);
	UTEST_add_testcase(test_foo_max_param2_param2_out);
	UTEST_add_testcase(test_foo_min_param1_param1_equal);
	UTEST_add_testcase(test_foo_min_param1_param1_greater);
	UTEST_add_testcase(test_foo_min_param1_param2_out);
	UTEST_add_testcase(test_foo_neg_param1);
	UTEST_add_testcase(test_foo_neg_param2);
	UTEST_add_testcase(test_foo_neg_params);

	UTEST_perform_all();

	UTEST_summary();

	while(1);
	return(0);
}
