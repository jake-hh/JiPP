#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// double funkcja(double x, double (*f)(double)) {
double funkcja(double x, double f(double)) {
	return x * x + (*f)(x);
}

int main() {
	double x = 0.0;
	printf("dla x = %g, f(x) = %g\n", x, funkcja(x, sin));
	printf("dla x = %g, f(x) = %g\n", x, funkcja(x, cos));
	return 0;
}