#include "task2.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
double f1(double x) { return x; }
double f2(double x) { return x * x; };
double f3(double x) { return sqrt(x); }
double f4(double x) { return 1 / x; }
void test1() { assert(fabs(integration(f1, -1, 1, 10000) - 0) < 1E-5); }
void test2() { assert(fabs(integration(f2, 0, 1, 1000000) - 0.333333) < 1E-6); }
void test3() { assert(fabs(integration(f3, 1, 5, 10000) - 6.7868) < 1E-4); }
void test4() { assert(fabs(integration(f4, 5, 9, 100000) - 0.58778) < 1E-5); }
int main() {
  test1();
  test2();
  test3();
  test4();
  printf("The test was completed successfully\n");
  return 0;
}
