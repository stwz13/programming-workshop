#include "integral.h"
#include <assert.h>
#include <math.h>

double linear(double x) { return x; }
double quadratic(double x) { return x * x; }
double reciprocal(double x) { return 1 / x; }
double square_root(double x) { return sqrt(x); }
double sine(double x) { return sin(x); }

void test_integrate_linear() {
  assert(fabs(integration(linear, 5, 15, 100000) - 100.0) < 1e-2);
}

void test_integrate_quadratic() {
  assert(fabs(integration(quadratic, 7, 35, 100000000) - 14177.33333) < 1e-3);
}

void test_integrate_reciprocal() {
  assert(fabs(integration(reciprocal, 5, 9, 100000) - 0.587) < 1e-3);
}

void test_integrate_square_root() {
  assert(fabs(integration(square_root, 3, 5, 100000000) - 3.98) < 1e-2);
}

void test_integrate_sine() {
  assert(fabs(integration(sine, 1, 3, 100000) - 1.53) < 1e-3);
}

int main() {
  test_integrate_linear();
  test_integrate_quadratic();
  test_integrate_reciprocal();
  test_integrate_square_root();
  test_integrate_sine();
  return 0;
}
