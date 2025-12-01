#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#pragma warning (disable: 4996)

const char* filename = "lab4.txt";

double ff(double x);


int main(int argc, char* argv[]) {
	double x = 0, a = 0, b = 0, dx = 0, y = 0;
	int ret = -1;

	FILE* fp = NULL;
	fp = fopen(filename, "w");

	if (fp == NULL) {
		printf("Nie można otworzyć pliku %s\n", filename);
		return 1;
	}

	// Get input data
	printf("Program do tablicowania funkcji w przedziale [a,b] z krokiem dx\n");
	printf("Podaj liczby a, b, dx: ");

	ret = scanf("%lf%lf%lf", &a, &b, &dx);
	printf("\n");

	// Print input data
	printf("a = %i\n", a);
	printf("b = %i\n", b);
	printf("dx = %i\n", dx);

	// Check if scanf has read 3 variables
	if (ret != 3) {
		printf("Blad przy wczytaniu\n");
		return 2;
	}

	// Calculate
	for (x = a; x <= b; x += dx) {
		y = ff(x);
		printf("\t%10.2lf\t\t%15.4lf\n", x, y);
		fprintf(fp, "\t%10.2lf\t\t%15.4lf\n", x, y);
	}

	printf("---------------------------------------------------------\n");

	// Close file
	fclose(fp);
	fp = NULL;
	return 0;
}

double ff(double x) {
	return 1.0 / (x * x + sqrt(1 + 2 * x + 3 * x * x));
}