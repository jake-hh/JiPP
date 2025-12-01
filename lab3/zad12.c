#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

int szereg_n(int n);


int main(int argc, char* argv[]) {
	int n = 0, ret = -1;

	// Get input data
	printf("Program do wyznaczania sumy n kolejnych liczb naturalnych\n");
	printf("Podaj liczbę n: ");

	ret = scanf("%i", &n);
	printf("\n");

	// Print input data
	printf("n = %i\n", n);

	// Check if scanf has read 1 variable
	if(ret != 1) {
		printf("Blad przy wczytaniu\n");
		return 1;
	}

	// Check requirement
	if (n < 0) {
		printf("Liczba musi być liczbą naturalną\n");
		return 1;
	}

	// Calculate sum
	int suma = szereg_n(n);

	printf("Suma n liczb = %i\n", suma);
	printf("---------------------------------------------------------\n");

	return 0;
}

int szereg_n(int n) {
	if (n <= 1) {
		if (n == 1)
			return 1;
		else
			return 0;
	}

	return szereg_n(n - 1) + n;
}