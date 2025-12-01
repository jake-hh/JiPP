#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

void zamien(int *x, int *y);


int main(int argc, char* argv[]) {
	int a = 0, b = 0;
	int ret = -1;

	// Get input data
	printf("Program do zamiany dwóch liczb\n");
	printf("Podaj 2 liczby a, b: ");

	ret = scanf("%i%i", &a, &b);
	printf("\n");

	// Print input data
	printf("a = %i\n", a);
	printf("b = %i\n", b);

	// Check if scanf has read 2 variables
	if(ret != 2) {
		printf("Blad przy wczytaniu\n");
		return 1;
	}

	// Swap numbers
	printf("------------------------ zamiana ------------------------\n");
	zamien(&a, &b);

	printf("a = %i\n", a);
	printf("b = %i\n", b);
	printf("---------------------------------------------------------\n");

	return 0;
}

// better alternative would be for example std::swap
void zamien(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}