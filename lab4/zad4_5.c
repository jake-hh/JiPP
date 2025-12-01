#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

int silnia(int n);


int main(int argc, char* argv[]) {
	int n = 0, ret = -1;

	// Get input data
	printf("Program do wyznaczania silni z n\n");
	printf("Podaj liczbę n: ");

	ret = scanf("%i", &n);
	printf("\n");

	// Print input data
	printf("n = %i\n", n);

	// Check if scanf has read 1 variable
	if (ret != 1) {
		printf("Blad przy wczytaniu\n");
		return 1;
	}

	// Check requirement
	if (n < 0) {
		printf("Liczba musi być liczbą naturalną\n");
		return 1;
	}

	// Calculate sum
	int s = silnia(n);

	printf("Silnia z n = %i\n", s);
	printf("---------------------------------------------------------\n");

	return 0;
}

int silnia(int n) {
	int r = 1;

	for (int i = 1; i <= n; i++)
		r *= i;

	return r;
}