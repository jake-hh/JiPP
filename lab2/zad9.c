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
	printf("Program do obliczania zespolonych pierwiastkow równania kwadratowego\n");
	printf("-------------------- a*x^2+b*x+c = 0 ------------------------------\n\n");
	printf("Podaj a,b,c\n");

	ret = scanf("%le%le%le", &a, &b, &c);

	// Check if scanf has read 3 variables
	if(ret != 3) {
		printf("Blad przy wczytaniu\n");
		printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);
		my_exit();
	}

	// Check a coefficient
	if (a == 0.0) {
		printf("To nie jest rownanie kwadratowe: a = 0\n");
		my_exit();
	}

	// Calculate delta
	double d = b*b-4.0*a*c;

	printf("Rownanie kwadratowe: %lf x^2 + %lf x + %lf = 0\n\n", a, b, c);

	// Check delta
	if(d >= 0.0) {
		// Computing real roots
		double p1, p2, x1, x2;
		p1 = -b/(2.0*a);
		p2 = sqrt(d)/(2.0*a);
		x1 = p1+p2;
		x2 = p1-p2;
		printf("Pierwiastki rzeczywsite: x1 = %e x2 = %e\n", x1, x2);
	}

	else {
		printf("delta = %e\n", d);

		// Computing complex roots
		double re, im, x1Re, x1Im, x2Re, x2Im;
		re = -b/(2.0*a);
		im = sqrt(fabs(d))/(2.0*a);

		printf("Pierwiastki zespolone: x1 = %e + %ei x2 = %e + %ei\n", re, im, re, -im);
	}

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