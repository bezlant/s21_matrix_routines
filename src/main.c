#include "tests/test_s21_matrix.h"

int main(void) {
    srand(time(0));
    run_tests();

    return 0;
}

void run_testcase(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 1)
        putchar('\n');
    printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
    counter_testcase++;

    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
}

void run_tests(void) {
    Suite *list_cases[] = {
        suite_s21_create_matrix(),      suite_s21_eq_matrix(),
        suite_s21_sum_matrix(),         suite_s21_sub_matrix(),
        suite_s21_mult_number_matrix(), suite_s21_mult_matrix(),
        suite_s21_transpose_matrix(),   NULL};

    for (Suite **current_testcase = list_cases; *current_testcase != NULL;
         current_testcase++) {
        run_testcase(*current_testcase);
    }
}

double get_rand(double min, double max) {
    double val = (double)rand() / RAND_MAX;
    return min + val * (max - min);
}
