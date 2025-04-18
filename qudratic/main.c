#include "solving_the_quadratic_equation.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test_a_zero_returns_error() {
  double *solutions = NULL;
  assert(solutions_of_quadratic_equation(0, 1, 1, 1E-7, &solutions) == -1 &&
         solutions == NULL);
  free(solutions);
}

void test_two_roots_standard() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1, 1E-7, &solutions);

  assert(count_of_roots == 2 && fabs(solutions[0] + 1) < 1E-7 &&
         fabs(solutions[1] - 1) < 1E-7);
  free(solutions);
}

void test_one_root_at_zero() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, 0, 1E-7, &solutions);
  assert(count_of_roots == 1 && fabs(solutions[0]) < 1E-7);
  free(solutions);
}

void test_no_real_roots_discriminant_lt_zero() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, 1, 1E-7, &solutions);
  assert(count_of_roots == -2 && solutions == NULL);
  free(solutions);
}

void test_small_c_precision_handling() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1E-7, 1E-7, &solutions);
  assert(count_of_roots == 2 && fabs(solutions[0] + 3E-4) < 1E-4 &&
         fabs(solutions[1] - 3E-4) < 1E-4);
  free(solutions);
}

void test_large_coefficients() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, -1E+10, -1, 1E-11, &solutions);
  assert(count_of_roots == 2 && fabs(solutions[0] + 1E-10) < 1E-4 &&
         fabs(solutions[1] - 1E+10) < 1E-4);
  free(solutions);
}

void test_single_root_near_zero() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1E-8, 1E-7, &solutions);
  assert(count_of_roots == 1 && fabs(solutions[0]) < 1E-7);
  free(solutions);
}

int main() {
  test_a_zero_returns_error();
  test_two_roots_standard();
  test_one_root_at_zero();
  test_no_real_roots_discriminant_lt_zero();
  test_small_c_precision_handling();
  test_large_coefficients();
  test_single_root_near_zero();
  return 0;
}
