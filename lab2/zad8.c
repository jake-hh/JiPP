#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

	double x = 3.14, y = 12.56, z = 7, w1, w2, w3, w4, w5;
	int k = 2, m = 4;

	w1 = pow(x / (y * z), 1./3) * log(x * x + pow(y,2));

	w2 = sin(k * x / 2) * cos(m * y) + y* exp(2*x - 1);

	w3 = fabs(x / (2*y*y + 1)) + sqrt(y / (z*z + 3)) + 5 * pow(y + z, 3);

	w4 = x / y / z * pow(z + 1, 1./3) + pow(x*x + z*z + 1, 1./k) - fabs(y);

	w5 = 1. / sqrt(x*x + y*y + k*k) + 1 / x * sin(k * y);

	printf("w1 = %f\n", w1);
	printf("w2 = %f\n", w2);
	printf("w3 = %f\n", w3);
	printf("w4 = %f\n", w4);
	printf("w5 = %f\n", w5);

	return 0;
}