#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#pragma warning (disable: 4996)

// Declare helper fns
static void my_exit();
static void my_return();


int main(int argc, char* argv[]) {

	double a = 0, b = 0, c = 0;
	int ret = -1;

	// Get input data
	printf("Program do obliczania pola trójkąta i promienia koła wpisanego\n");
	printf("Podaj boki trójkąta: a,b,c\n");

	ret = scanf("%le%le%le", &a, &b, &c);
	printf("\n");

	// Print input data
	printf("Boki trójkąta\n");
	printf("a = %e\n", a);
	printf("b = %e\n", b);
	printf("c = %e\n\n", c);

	// Check if scanf has read 3 variables
	if(ret != 3) {
		printf("Blad przy wczytaniu\n");
		my_exit();
	}

	// Check triangle requirement
	if (a <= 0 || b <= 0 || c <= 0 || a >= b+c || b >= c+a || c >= a+b) {
		printf("Trójkąt nie istnieje\n");
		my_exit();
	}

	// Calculate properties
	double p = (a+b+c)/2;                  // halfed perimeter
	double s = sqrt(p*(p-a)*(p-b)*(p-c));  // area
	double r = s/p;                        // radius

	printf("Pole trójkąta = %e\n", s);
	printf("Promień koła wpisanego = %e\n", r);
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