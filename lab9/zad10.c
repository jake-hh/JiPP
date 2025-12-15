#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct CO {
	double re;
	double im;
} COMPLEX;


int pierw_complex(double a, double b, double c, COMPLEX *x1, COMPLEX *x2) {
	if (a == 0.0) {
		printf("To nie jest rownanie kwadratowe: a = 0\n");
		return 1;
	}

	double p = -b / (2 * a);
	double q = c / a;
	double delta = p * p - q;

	if (delta >= 0.0) {
		double r_delta = sqrt(delta);
		x1->re = p + r_delta;
		x1->im = 0;
		x2->re = p - r_delta;
		x2->im = 0;
	}
	else {
		double r_delta = sqrt(-delta);
		x1->re = p;
		x1->im = r_delta;
		x2->re = p;
		x2->im = -r_delta;
	}

	return 0;
}


COMPLEX add_complex(COMPLEX a, COMPLEX b) {
	COMPLEX c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}


int main() {
	COMPLEX a, b;

	pierw_complex(4, 4, 4, &a, &b);

	COMPLEX c = add_complex(a, b);

	printf("a.re = %g, a.im = %g\n", a.re, a.im);
	printf("b.re = %g, b.im = %g\n", b.re, b.im);
	printf("c.re = %g, c.im = %g\n", c.re, c.im);
	return 0;
}

