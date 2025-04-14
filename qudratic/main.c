#include "solving_the_quadratic_equation.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test1() {
  double *solutions = NULL;
  assert(solutions_of_quadratic_equation(0, 1, 1, 1E-7, &solutions) == -1 &&
         solutions == NULL);
  free(solutions);
}

void test2() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1, 1E-7, &solutions);

  assert(count_of_roots == 2 && fabs(solutions[0] + 1) < 1E-7 &&
         fabs(solutions[1] - 1) < 1E-7);
  free(solutions);
}

void test3() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, 0, 1E-7, &solutions);
  assert(count_of_roots == 1 && fabs(solutions[0]) < 1E-7);
  free(solutions);
}

void test4() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, 1, 1E-7, &solutions);
  assert(count_of_roots == -2 && solutions == NULL);
  free(solutions);
}

void test5() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1E-7, 1E-7, &solutions);
  assert(count_of_roots == 2 && fabs(solutions[0] + 3E-4) < 1E-4 &&
         fabs(solutions[1] - 3E-4) < 1E-4);
  free(solutions);
}

void test6() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, -1E+10, -1, 1E-11, &solutions);
  assert(count_of_roots == 2 && fabs(solutions[0] + 1E-10) < 1E-4 &&
         fabs(solutions[1] - 1E+10) < 1E-4);
  free(solutions);
}

void test7() {
  double *solutions;

  int count_of_roots =
      solutions_of_quadratic_equation(1, 0, -1E-8, 1E-7, &solutions);
  assert(count_of_roots == 1 && fabs(solutions[0]) < 1E-7);
  free(solutions);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  return 0;
}
