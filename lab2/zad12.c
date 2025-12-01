#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning (disable: 4996)

// Declare helper fns
static void my_exit();
static void my_return();
static void check(double x);

static double triangle();
static double square();
static double rectangle();
static double circle();


int main(int argc, char* argv[]) {

	char type = 'x';
	double s = 0.0;

	// Get input data
	printf("Program do obliczania pola figury\n");
	printf("Podaj rodzaj figury: [T] trójkąt, [K] kwadrat, [P] prostokąt, [O] koło\n");

	scanf("%c", &type);
	printf("\n");

	switch (type) {
		case 'T':
		case 't':
		s = triangle();
		break;

		case 'K':
		case 'k':
		s = square();
		break;

		case 'P':
		case 'p':
		s = rectangle();
		break;

		case 'O':
		case 'o':
		s = circle();
		break;

		default:
		printf("Niepoprawne dane\n");
		my_exit();
	}

	printf("Pole figury S = %e\n", s);
	printf("---------------------------------------------------------\n");
	my_return();
}


void check(double x) {
	if (x <= 0) {
		printf("Wartość mniejsza od 0. Figura nie istnieje\n");
		my_exit();
	}
}


double triangle() {
	double a = 0, b = 0, c = 0;
	int ret = -1;

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
	check(a);
	check(b);
	check(c);

	if (a >= b+c || b >= c+a || c >= a+b) {
		printf("Trójkąt nie istnieje\n");
		my_exit();
	}

	// Calculate area
	double p = (a+b+c)/2;                  // halfed perimeter
	double s = sqrt(p*(p-a)*(p-b)*(p-c));

	return s;
}


double square() {
	double a = 0;
	int ret = -1;

	printf("Podaj bok kwadratu: a\n");

	ret = scanf("%le", &a);
	printf("\n");

	// Print input data
	printf("Bok kwadratu\n");
	printf("a = %e\n\n", a);

	// Check if scanf has read 3 variables
	if(ret != 1) {
		printf("Blad przy wczytaniu\n");
		my_exit();
	}

	// Check input data
	check(a);

	// Calculate area
	double s = a*a;

	return s;
}


double rectangle() {
	double a = 0, b = 0;
	int ret = -1;

	printf("Podaj boki prostokąta: a,b\n");

	ret = scanf("%le%le", &a, &b);
	printf("\n");

	// Print input data
	printf("Boki prostokąta\n");
	printf("a = %e\n", a);
	printf("b = %e\n\n", b);

	// Check if scanf has read 3 variables
	if(ret != 2) {
		printf("Blad przy wczytaniu\n");
		my_exit();
	}

	// Check input data
	check(a);
	check(b);

	// Calculate area
	double s = a*b;

	return s;
}


double circle() {
	double r = 0;
	int ret = -1;

	printf("Podaj promień koła: r\n");

	ret = scanf("%le", &r);
	printf("\n");

	// Print input data
	printf("Promień koła\n");
	printf("r = %e\n\n", r);

	// Check if scanf has read 3 variables
	if(ret != 1) {
		printf("Blad przy wczytaniu\n");
		my_exit();
	}

	// Check input data
	check(r);

	// Calculate area
	double s = M_PI*r*r;

	return s;
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