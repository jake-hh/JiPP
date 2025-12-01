#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning (disable: 4996)

void kolo(double r, double *w1, double *w2);


int main(int argc, char* argv[]) {
	double r = 0, s = 0, l = 0;
	int ret = -1;

	// Get input data
	printf("Program do obliczania pola i obwodu koła\n");
	printf("Podaj promień koła r: ");

	ret = scanf("%le", &r);
	printf("\n");

	// Print input data
	printf("r = %g\n", r);

	// Check if scanf has read 1 variable
	if(ret != 1) {
		printf("Blad przy wczytaniu\n");
		return 1;
	}

	// Check circle requirement
	if (r <= 0) {
		printf("Koło nie istnieje\n");
		return 1;
	}

	// Calculate properties
	kolo(r, &s, &l);

	printf("Pole koła = %g\n", s);
	printf("Obwód koła = %g\n", l);
	printf("---------------------------------------------------------\n");

	return 0;
}

void kolo(double r, double *w1, double *w2) {
	*w1 = M_PI*r*r;
	*w2 = M_PI*2*r;
}