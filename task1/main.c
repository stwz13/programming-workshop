#include "task1.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void test1() {
  double *ans = solution_of__quadratic_equation(0, 1, 1, 10E-7, 10E-7);
  assert(fabs(ans[0] + 1) < 1E-7);
  free(ans);
}
void test2() {
  double *ans = solution_of__quadratic_equation(1, 0, -1, 1E-7, 1E-7);
  assert(fabs(ans[0] - 2) < 1E-7 && fabs(ans[1] + 1) < 1E-7 &&
         fabs(ans[2] - 1) < 1E-7);
  free(ans);
}
void test3() {
  double *ans = solution_of__quadratic_equation(1, 0, 0, 1E-7, 1E-7);
  assert(fabs(ans[0] - 1) < 1E-7 && fabs(ans[1] - 0) < 1E-7);
  free(ans);
}
void test4() {
  double *ans = solution_of__quadratic_equation(1, 0, 1, 1E-7, 1E-7);
  assert(fabs(ans[0] - 0) < 1E-7);
  free(ans);
}
void test5() {
  double *ans = solution_of__quadratic_equation(1, 0, -1E-7, 1E-4, 1E-7);
  assert(fabs(ans[0] - 2) < 1E-4 && fabs(ans[1] + 3E-4) < 1E-4 &&
         fabs(ans[2] - 3E-4) < 1E-4);
  free(ans);
}
void test6() {
  double *ans = solution_of__quadratic_equation(1, -1E+10, -1, 1E-11, 1E-11);
  assert(fabs(ans[0] - 2) < 10E-11 && fabs(ans[1] + 1E-10) < 10E-11 &&
         fabs(ans[2] - 1E+10) < 10E-11);
  free(ans);
}
void test7() {
  double *ans = solution_of__quadratic_equation(1, 0, -1E-8, 1E-7, 1E-7);
  assert(fabs(ans[0] - 1) < 1E-7 && fabs(ans[1] - 0) < 1E-7);
  free(ans);
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