#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int sign(double a) {

  if (a >= 0)
    return 1;
  else
    return -1;
}
double tolerance(double a, double eps) {
  if (fabs(a) < eps)
    return 0.0;
  else
    return a;
}
double *solution_of__quadratic_equation(double a, double b, double c,
                                        double eps, double disriminant_eps) {
  double *solutions = NULL;
  if (fabs(a) < eps) {
    printf("a is negligible\n");
    solutions = malloc(sizeof(double));
    solutions[0] = -1;
  } else {
    b = b / a;
    c = c / a;
    double discriminant = b * b - 4 * c;
    if (fabs(discriminant) < disriminant_eps) {
      solutions = malloc(2 * sizeof(double));
      solutions[0] = 1;
      solutions[1] = tolerance(-b / 2, eps);
    } else if (discriminant < 0) {
      solutions = malloc(sizeof(double));
      solutions[0] = 0;
    } else {
      solutions = malloc(3 * sizeof(double));
      solutions[0] = 2;
      solutions[1] = tolerance(-(b + sign(b) * sqrt(discriminant)) / 2, eps);
      solutions[2] = tolerance(c / solutions[1], eps);
      if (solutions[1] > solutions[2]) {
        double copy = solutions[1];
        solutions[1] = solutions[2];
        solutions[2] = copy;
      }
    }
  }
  return solutions;
}