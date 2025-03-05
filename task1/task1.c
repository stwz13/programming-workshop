#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double rounding(double x) {
  int n;
  double copy = x;
  if ((int)(x * 10) % 10 != 0 || x - (int)x == 0)
    return x;
  else {
    x = x - (int)x;
    for (n = 0; (int)(x) % 10 == 0; n++)
      x *= 10;
    int last_digit = ((int)x) % 10;
    double ans = (int)copy + last_digit * pow(10, (-n));
    return ans;
  }
}
double *solution(double a, double b, double c) {
  double x1, x2;
  double *solutions = malloc(2 * sizeof(int));
  double discriminant = b * b - 4 * a * c;
  if (a == 0) {
    printf("The equation is not quadratic");
    solutions = NULL;
  } else {
    if (discriminant == 0) {
      x1 = ((-b / (2 * a)));
      solutions[0] = rounding(x1);
    } else if (discriminant > 0) {
      x1 = rounding(((-b + sqrt(discriminant)) / (2 * a)));
      x2 = rounding(((-b - sqrt(discriminant)) / (2 * a)));
      solutions[0] = x1 > x2 ? x2 : x1;
      solutions[1] = x1 > x2 ? x1 : x2;
    } else {
      printf("The equation has no roots");
      solutions = NULL;
    }
  }
  return solutions;
}
