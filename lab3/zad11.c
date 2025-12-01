#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

int funkcja(double x, double y, double *z);


int main(int argc, char* argv[]) {
	double x = 0, y = 0, z = 0;
	int ret = -1, n = 0;

	// Get input data
	printf("Program do liczenia wartości 'z' z funkcji\n");
	printf("Podaj 2 liczby x, y: ");

	ret = scanf("%le%le", &x, &y);
	printf("\n");

	// Print input data
	printf("x = %g\n", x);
	printf("y = %g\n", y);

	// Check if scanf has read 2 variables
	if(ret != 2) {
		printf("Blad przy wczytaniu\n");
		return 1;
	}

	// Calculate
	n = funkcja(x, y, &z);

	printf("z = %g\n", z);
	printf("n = %i\n", n);
	printf("---------------------------------------------------------\n");

	return 0;
}

int funkcja(double x, double y, double *z) {

	if (x*x + y*y <= 1) {
		*z = x*x + y;
		return 1;
	}
	else if (y > x + 5) {
		*z = 2*x + y*y;
		return 2;
	}
	else {
		*z = 0.5*x*x + y;
		return 3;
	}
}