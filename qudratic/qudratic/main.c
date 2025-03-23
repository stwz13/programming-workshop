#include "solving_the_quadratic_equation.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test1() {
  int completion;
  double *solutions =
      solutions_of_quadratic_equation(0, 1, 1, 1E-7, &completion);

  assert(completion == -1 && solutions == NULL);
}

void test2() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, 0, -1, 1E-7, &completion);

  assert(completion == 2 && fabs(solutions[0] + 1) < 1E-7 &&
         fabs(solutions[1] - 1) < 1E-7);
}

void test3() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, 0, 0, 1E-7, &completion);
  assert(completion == 1 && fabs(solutions[0]) < 1E-7);
}

void test4() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, 0, 1, 1E-7, &completion);
  assert(completion == -2 && solutions == NULL);
}

void test5() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, 0, -1E-7, 1E-7, &completion);
  assert(completion == 2 && fabs(solutions[0] + 3E-4) < 1E-4 &&
         fabs(solutions[1] - 3E-4) < 1E-4);
}

void test6() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, -1E+10, -1, 1E-11, &completion);
  assert(completion == 2 && fabs(solutions[0] + 1E-10) < 1E-4 &&
         fabs(solutions[1] - 1E+10) < 1E-4);
}

void test7() {
  int completion;

  double *solutions =
      solutions_of_quadratic_equation(1, 0, -1E-8, 1E-7, &completion);
  assert(completion == 1 && fabs(solutions[0]) < 1E-7);
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
