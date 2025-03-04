//[a,b] - интегрируемый отрезок, n - число узлов интегрирования, b > a
#include <stdio.h>

double integration(double (*f)(double), double a, double b, int n) {
  double h = (b - a) / n;
  double s = 0.0;
  for (double i = a; i < b - h; i += h)
    s += (f(i) + f(i + h)) / 2 * h;
  return s;
}