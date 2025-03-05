#include "task1.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
void test1() {
  double *ans = solution(1, 0, -1);
  assert(fabs(ans[0] + 1) < 10E-7 && fabs(ans[1] - 1) < 10E-7);
}
void test2() {
  double *ans = solution(1, 0, 0);
  assert(fabs(ans[0] - 0) < 10E-7);
}
void test3() {
  double *ans = solution(1, 0, 1);
  assert(ans == NULL);
}
void test4() {
  double *ans = solution(1, 0, -1E-7);
  assert(fabs(ans[0] - -3E-4) < 10E-7 && fabs(ans[1] - 3E-4) < 10E-7);
}
void test5() {
  double *ans = solution(1, -1E+10, -1);
  assert(fabs(ans[0] - -1E-10) < 10E-7 && fabs(ans[1] - 1E+10) < 10E-7);
}
void test7() {
  double *ans = solution(1, 0, -1E-8);
  assert(fabs(ans[0] - 0) < 10E-7);
}
int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test7();
}
