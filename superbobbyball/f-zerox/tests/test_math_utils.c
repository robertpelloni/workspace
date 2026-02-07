#include <stdio.h>
#include "minunit.h"
#include "../include/pc/ultra64.h"
#include "../include/functions.h"

int tests_run = 0;

// Declaration of function from game_2B20.c (if not in header)
// s32 func_8006A9E0(f32 arg0); // Already in functions.h

static char * test_math_roundf() {
    mu_assert("Round 0.0 failed", func_8006A9E0(0.0f) == 0);
    mu_assert("Round 0.5 failed", func_8006A9E0(0.5f) == 1);
    mu_assert("Round 0.4 failed", func_8006A9E0(0.4f) == 0);
    mu_assert("Round -0.5 failed", func_8006A9E0(-0.5f) == -1);
    mu_assert("Round -0.4 failed", func_8006A9E0(-0.4f) == 0);
    mu_assert("Round 1.9 failed", func_8006A9E0(1.9f) == 2);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_math_roundf);
    return 0;
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    char *result = all_tests();
    if (result != 0) {
        printf("TEST FAILED: %s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
