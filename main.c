#include "task2.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
double f1(double x) { return x; }
double f2(double x) { return x * x; };
double f3(double x) { return sqrt(x); }
double f4(double x) { return sin(x); }
double f5(double x) { return 1 / x; }
void test1() { assert(abs(integration(f1, -1, 1, 10) - 0) < 10E-7); }
void test2() { assert(abs(integration(f2, 0, 1, 100000) - 0.333) < 10E-7); }
void test3() { assert(abs(integration(f3, 1, 5, 100) - 6.78) < 10E-7); }
void test4() { assert(abs(integration(f4, 1, 3.14 / 2, 1000) - 1) < 10E-7); }
void test5() { assert(abs(integration(f5, 5, 9, 1000000) - 0.58) < 10E-7); }
int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
}