#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

// Declare helper fns
static void my_exit();
static void my_return();


int main(int argc, char* argv[]) {

	double a[4] = {0, 0, 0, 0};
	int ret = -1;

	// Get input data
	printf("Program do znajdowania największej liczby\n");
	printf("Podaj cztery liczby: a1,a2,a3,a4\n");

	ret = scanf("%le%le%le%le", &a[0], &a[1], &a[2], &a[3]);
	printf("\n");

	// Print input data
	printf("Wpisane liczby\n");
	for (int i = 0; i < 4; i++)
		printf("%d: %e\n", i, a[i]);
	printf("\n");

	// Check if scanf has read 3 variables
	if(ret != 4) {
		printf("Blad przy wczytaniu\n");
		my_exit();
	}

	// Find max value
	int max_i = 0;

	for (int i = 0; i < 4; i++)
		if (a[i] > a[max_i])
			max_i = i;

	printf("Największa liczba to a%d = %e", max_i, a[max_i]);

	printf("---------------------------------------------------------\n");
	my_return();
}

void my_exit() {
	/*==============================================================================
	Przymusowe zakonczenie wykonania
	Zawiesza monitor dok№d nie bкdzie wprowadzony ^Z
	exit(1)
	===============================================================================*/
	int ch;
	printf("Zakoncz - ctrl+Z Enter\n");
	while((ch = getchar()) != EOF);

	exit(1);
}

void my_return() {
	/*==============================================================================
	Normalne zakonczenie
	Zawiesza monitor dok№d nie bкdzie wprowadzony ^Z
	exit(0)
	===============================================================================*/
	int ch;

	printf("Zakoncz - ctrl+Z Enter\n");
	while((ch = getchar()) != EOF);

	exit(0);
}