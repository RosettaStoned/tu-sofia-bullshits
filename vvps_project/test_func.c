#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CUnit/CUnit.h"
#include "CUnit/Automated.h"

/**//*---- functions to be tested ------*/
extern void solve(double *table, int row, int col, double *result);

void test_first()
{
    double table[6][4] = {
        { 345, 65, 23, 31.4 },
        { 168, 18, 18, 14.6 },
        { 94, 0, 0, 6.4 },
        { 187, 185, 98, 28.3 },
        { 621, 87, 10, 42.1 },
        { 255, 0, 0, 15.3 }
    };

    double result[4];
    solve(*(table), 6, 4, result);

    double expected_result[] = {
        0.566457,
        0.0653293,
        0.00871874,
        0.151049
    };

    int i;
    for(i = 0; i < 4; i++) {
        printf("RESULT: %g -> EXPECTED: %g\n", result[i], expected_result[i]);
        CU_ASSERT_DOUBLE_EQUAL(result[i], expected_result[i], 0.0005);
    }

}

void test_sec()
{

    double table[6][4] = {
        { 1142, 1060, 325, 201 },
        { 863, 995, 98, 98 },
        { 1065, 3205, 23, 162 },
        { 554, 120, 0, 54 },
        { 983, 2896, 120, 138 },
        { 256, 485, 88, 61 }
    };

    double result[4];
    solve(*(table), 6, 4, result);

    double expected_result[] = {
        6.70134,
        0.078366,
        0.0150413,
        0.246056
    };

    int i;
    for(i = 0; i < 4; i++) {
        printf("RESULT: %g -> EXPECTED: %g\n", result[i], expected_result[i]);
        CU_ASSERT_DOUBLE_EQUAL(result[i], expected_result[i], 0.0005);
    }
}

void test_zeroes()
{
    double table[6][4] = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    double result[4];
    solve(*(table), 6, 4, result);
    
    CU_ASSERT(0);
}

CU_TestInfo testcases[] = {
    {"Testing with first table: ", test_first},
    {"Testing with second table: ", test_sec},
    {"Testing with only zeroes table: ", test_zeroes},
    CU_TEST_INFO_NULL
};
/**//*---- test suites ------------------*/
int suite_success_init(void) { return 0; }
int suite_success_clean(void) { return 0; }

CU_SuiteInfo suites[] = {
    {"Testing the function gauss():", suite_success_init, suite_success_clean, NULL, NULL, testcases},
    CU_SUITE_INFO_NULL
};

/**//*---- setting enviroment -----------*/
void add_tests()
{
    assert(NULL != CU_get_registry());
    assert(!CU_is_test_running());
    /**//* shortcut regitry */

    if(CUE_SUCCESS != CU_register_suites(suites)){
        fprintf(stderr, "Register suites failed - %s ", CU_get_error_msg());
        exit(1);
    }
}

