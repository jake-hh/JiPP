#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);
double fp(double);
double g(double);
double gp(double);

void test_newton(double x0, int n, double eps, char name, double(*f)(double), double(*fp)(double));
int newton(double *x, int n, double eps, double(*f1)(double), double(*f2)(double));


int main() {
	double eps = 0.001;
	int n = 100;

	/* dla f start 0.5 -> 0 0.8 -> -1.8954 1.0 -> 1.8954 */
	test_newton(0.5, n, eps, 'f', f, fp);
	test_newton(0.8, n, eps, 'f', f, fp);
	test_newton(1.0, n, eps, 'f', f, fp);

	/* dla g start 0.2 -> 1.5 0.8 -> -1.8954 1.0 -> 1.8954 */
	test_newton(0.2, n, eps, 'g', g, gp);
	test_newton(0.8, n, eps, 'g', g, gp);
	test_newton(1.0, n, eps, 'g', g, gp);
	test_newton(0.5, n, eps, 'g', g, gp);
	test_newton(-1.2, n, eps, 'g', g, gp);
}

int newton(double *x, int n, double eps, double(*f1)(double), double(*f2)(double)) {
	double x1;
	int i = 0;

	do {
		x1 = -(*f1)(*x) / (*f2)(*x);
		*x += x1;
		if (fabs(x1) < eps) return 0;
	} while (i++ < n);

	return 1;
}

double f(double x) {
	return sin(x) - .5*x;
}

double fp(double x) {
	return cos(x) - .5;
}

double g(double x) {
	return tan(x) - 2.0*x;
}

double gp(double x) {
	return 1/pow(cos(x), 2.0) - 2.0;
}

void test_newton(double x0, int n, double eps, char name, double(*f)(double), double(*fp)(double)) {
	double start = x0;
	if (!newton(&x0, n, eps, f, fp))
		printf("%c: start= %g rozwiazanie= %lf wart.= %lf\n", name, start, x0, f(x0));
	else
		printf("%c: start= %g Brak zbieznosci\n", name, start);
}