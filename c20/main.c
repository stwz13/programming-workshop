#include "integral.h"
#include <assert.h>
#include <math.h>

double funct1(double x) { return x; }
double funct2(double x) { return x * x; }
double funct3(double x) { return 1 / x; }
double funct4(double x) { return sqrt(x); }
double funct5(double x) { return sin(x); }

void test_linear_function() { assert(fabs(integration(funct1, 5, 15, 100000) - 100) < 1E-2); }
void test_quadratic_function()
{
  assert(fabs(integration(funct2, 7, 35, 100000000) - 14177.33333) < 1E-3);
}

void test_inverse_function()
{
  (assert(fabs(integration(funct3, 5, 9, 100000) - 0.587) < 1E-3));
}

void test_sqrt_function()
{
  (assert(fabs(integration(funct4, 3, 5, 100000000) - 3.98) < 1E-2));
}

void test_sine_function()
{
  (assert(fabs(integration(funct5, 1, 3, 100000) - 1.53) < 1E-3));
}

int main()
{
  test_linear_function();
  test_quadratic_function();
  test_inverse_function();
  test_sqrt_function();
  test_sine_function();
  return 0;
}
