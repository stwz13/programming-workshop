
#include <math.h>
#include <stdlib.h>
#define IS_NOT_QUADRATIC -1;
#define DISCRIMINANT_IS_NEGATIVE -2;

double *solutions_of_quadratic_equation(double a, double b, double c,
                                        double eps, int *completion) {

  double *solutions = NULL;

  if (fabs(a) < eps) {
    *completion = IS_NOT_QUADRATIC;
  } else {

    b = b / a;
    int sign_b = b >= 0 ? 1 : -1;

    c = c / a;
    double discriminant = b * b - 4 * c;

    if (fabs(discriminant) < eps) {

      *completion = 1;
      solutions = malloc(sizeof(double));

      solutions[0] = -b / 2;
    }

    else if (discriminant < -eps) {
      *completion = DISCRIMINANT_IS_NEGATIVE;
    }

    else {
      solutions = malloc(2 * sizeof(double));
      *completion = 2;

      double x1 = -(b + sign_b * sqrt(discriminant)) / 2;
      double x2 = c / x1;

      if (x2 > x1) {
        solutions[0] = x1;
        solutions[1] = x2;
      }

      else {
        solutions[0] = x2;
        solutions[1] = x1;
      }
    }
  }

  return solutions;
}
