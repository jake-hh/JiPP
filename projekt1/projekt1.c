#include <float.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define FILENAME "data.txt"

extern void error(int nr, char *msg);
void clear_stdin();
void print_table(long double a, long double b, long divs, long double delta_x, long double delta_y, int n);

enum STOP_REASON {
	UNKNOWN,
	MAX_N,
	MAX_PRECISION,
	BOTH_MAX
};


long double ff(long double x, long double delta_y, int n, int *stop_res, int *iterations) {
    long double y = 0;
    long double element;

    int i = 0;              // iteration
    long double x_i = x;    // nominator
    int sign = 1;

    do {
        //ln(1+x) // -1 < x <= 1 // x^1/1 - x^2/2 + x^3/3 - x^4/4 + ...
        element = sign * x_i / ++i;
        y += element;

        x_i *= x;
        sign *= -1;
    }
	while (fabs(element) > delta_y && i < n);

    if (fabs(element) <= delta_y)
        *stop_res = MAX_PRECISION;

    if (i >= n)
        *stop_res = MAX_N;

    if (i >= n && fabs(element) <= delta_y)
        *stop_res = BOTH_MAX;

    *iterations = i;
    return y;
}


int main() {

    //Wczytaj przedział
    //wczytaj ilość podziałów
    //Spradz czy delta nie jest < 1e-14

    printf("Program do tablicowania funkcji 𝑦 = 𝑓(𝑥)\n"
        "we wszystkich punktach podziału na 𝑛 części przedziału [𝑎, 𝑏].\n"
        "Funkcja 𝑓 dana jest w postaci rozwinięcia w szereg potęgowy i w postaci wzoru analitycznego.\n"
        "Obliczanie sumy szeregu wykonaj z dokładnością 𝜀.\n"
        "Sumuj co najwyżej 𝑀 wyrazów szeregu.\n\n");

    printf("f(x) = ln(1+x)\n");

    // printf("Zakres argumentu x e 
    printf("Interpretacja zakresu:\n---<A------B>--->x\n");
    printf("A <= x <= B\n"
        "Zakres musi znajdować się w przedziale -1 < x <= 1\n");


	long double a;
    printf("Podaj początek zakresu (A): ");
    fflush(stdin);
    if (scanf("%Lf", &a) != 1 || a <= -1 || a > 1 || isnan(a))
        error(1, "");
    clear_stdin();


	long double b;
    printf("Podaj koniec zakresu (B): ");
    if (scanf("%Lf", &b) != 1 || b < -1 || b > 1 || b <= a || isnan(b))
        error(1, "");
    clear_stdin();


    long divs;
    printf("Podaj ilość podziałów (2 <= divs < %ld; Liczba calkowita): ", LONG_MAX);
    if (scanf("%ld", &divs) != 1 || divs < 2)
        error(1, "");
    clear_stdin();


    long double delta_x = (b - a) / (long double) (divs-1);
    if (delta_x < LDBL_EPSILON)
        error(1, "Zbyt gęsty podział dla zadanego zakresu");


	long double delta_y;
    printf("Podaj dokładność wyników (0 < DeltaY < 1e-16; liczba rzeczywista): ");
    if (scanf("%Lf", &delta_y) != 1 || delta_y < 1e-16 || isnan(delta_y) || isinf(delta_y))
        error(1, "");
    clear_stdin();


    int n;
    printf("Podaj maksymalną ilość iteracji (0 < n < %d; Liczba całkowita): ", INT_MAX);
    if (scanf("%d", &n) != 1 || n < 1)
        error(1, "");
    clear_stdin();


	print_table(a, b, divs, delta_x, delta_y, n);
}


void clear_stdin() {
    while (getchar() != '\n');
}


void print_table(long double a, long double b, long divs, long double delta_x, long double delta_y, int n) {

    FILE *file = fopen(FILENAME, "w");

    if (file == NULL)
        error(2, FILENAME);


	const char *header = "Krok\t\tx\t\tf_szereg(x)\t\tf_analityczna(x)\t\tliczba wyrazów szeregu\t\tPowód zatrzymania\n";
    printf("%s", header);
    fprintf(file, "%s", header);

    long double x = a;

    for (long long i = 1; i <= divs; i++) {
        int stop_res = UNKNOWN;
        int iterations = 0;
        char *stop_msg;

        long double f_x = ff(x, delta_y, n, &stop_res, &iterations);

        switch (stop_res) {
            case MAX_N:
                stop_msg = "Osiągnięto maksymalną ilość iteracji";
                break;
            case MAX_PRECISION:
                stop_msg = "Osiągnieto żadaną dokładność";
                break;
            case BOTH_MAX:
                stop_msg = "Osiągnięto maksymalną ilość iteracji i maksymalną precyzję";
                break;
            default:
                stop_msg = "Praca nie spodziewana";
                fprintf(stderr, "%s\n"
                        "Used iterations = %d\n"
                        "n = %d\n"
                        "x = %.10Lg\n"
                        "F(x) = %.10Lg\t->\tln(1+x) = %.10g\n"
                        "divs = %ld\n"
                        "Delta x = %.10Lg\n"
                        "Delta y = %.10Lg\n\n", stop_msg, iterations, n, x, f_x, log(1+x), divs, delta_x, delta_y);
                error(4, "");
        }

		const char *format = "%-7lld %-15.6Le %-24.16Lg %-24.16Lg %-10d \t\t\t\t%s\n";

        printf(format, i, x, f_x, logl(1 + x), iterations, stop_msg);
        fprintf(file, format, i, x, f_x, logl(1 + x), iterations, stop_msg);

        x += delta_x;
    }

    fclose(file);
}