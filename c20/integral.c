
double integration(double (*f)(double), double a, double b, unsigned int n) {

  double h = (b - a) / n;

  double result = 0.0;

  for (int i = 0; i < n - 1; i++) {
    double x = a + h * i;
    result += (f(x) + f(x + h)) / 2 * h;
  }
  return result;
}
