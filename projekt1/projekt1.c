#include <float.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define FILENAME "data.txt"

#define ERR_PROG_CALL	0
#define ERR_USER_INPUT	1
#define ERR_FILE_OPEN	2
#define ERR_UNKNOWN		3

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

    printf("Program do tablicowania funkcji 𝑦 = 𝑓(𝑥)\n"
        "we wszystkich punktach podziału na 𝑛 części przedziału [𝑎, 𝑏].\n"
        "Funkcja 𝑓 dana jest w postaci rozwinięcia w szereg potęgowy i w postaci wzoru analitycznego.\n"
        "Obliczanie sumy szeregu wykonaj z dokładnością 𝜀.\n"
        "Sumuj co najwyżej 𝑀 wyrazów szeregu.\n\n");

    printf("f(x) = ln(1+x), x ∈ (-1, 1]\n\n");

    printf("x ∈ [a, b]\n");

	long double a;
    printf("Podaj początek zakresu, a ∈ (-1, 1]: ");
    fflush(stdin);
    if (scanf("%Lf", &a) != 1 || a <= -1 || a > 1 || isnan(a))
        error(ERR_USER_INPUT, "");
    clear_stdin();


	long double b;
    printf("Podaj koniec zakresu, b ∈ [a, 1]: ");
    if (scanf("%Lf", &b) != 1 || b <= -1 || b > 1 || b <= a || isnan(b))
        error(ERR_USER_INPUT, "");
    clear_stdin();


    long divs;
    printf("Podaj liczbę przedziałów 𝑛 ∈ [2, %ld) ∩ ℤ: ", LONG_MAX);
    if (scanf("%ld", &divs) != 1 || divs < 2)
        error(ERR_USER_INPUT, "");
    clear_stdin();


    printf("Obliczam Δx = (b - a) / 𝑛\n");
    if ((b - a) / (long double) (divs-1) < LDBL_EPSILON)
        error(ERR_USER_INPUT, "Zbyt gęsty podział dla zadanego zakresu");
    long double delta_x = (b - a) / (long double) (divs-1);


	long double delta_y;
    printf("Podaj dokładność elementów przy obliczaniu szeregu 𝜀 > 1e-14: ");
    if (scanf("%Lf", &delta_y) != 1 || delta_y < 1e-14 || isnan(delta_y) || isinf(delta_y))
        error(ERR_USER_INPUT, "");
    clear_stdin();


    int n;
    printf("Podaj maksymalną ilość iteracji 𝑀 ∈ [1, %d) ∩ ℤ: ", INT_MAX);
    if (scanf("%d", &n) != 1 || n < 1)
        error(ERR_USER_INPUT, "");
    clear_stdin();


	print_table(a, b, divs, delta_x, delta_y, n);
}


void clear_stdin() {
    while (getchar() != '\n');
}


void print_table(long double a, long double b, long divs, long double delta_x, long double delta_y, int n) {

    FILE *file = fopen(FILENAME, "w");
    if (!file)
        error(ERR_FILE_OPEN, FILENAME);

	//const char *header = "Krok\t\tx\t\t\t\tf_szereg(x)\t\t\tf_analityczna(x)\t\tliczba wyrazów\t\tPowód zatrzymania\n";
    const char *header = "%-7s %-15s %-24s %-24s %-15s  %s\n";
    printf(header, "krok", "x", "f_szereg(x)", "f_analit(x)", "liczba wyrazów", "Powód zatrzymania");
    fprintf(file, header, "krok", "x", "f_szereg(x)", "f_analit(x)", "liczba wyrazów", "Powód zatrzymania");

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
                stop_msg = "Nieznany powód zatrzymania";
                char err_msg[256];
                snprintf(err_msg, sizeof err_msg, "%s\n"
                        "Used iterations = %d\n"
                        "n = %d\n"
                        "x = %.10Lg\n"
                        "F(x) = %.10Lg\t->\tln(1+x) = %.10Lg\n"
                        "divs = %ld\n"
                        "Delta x = %.10Lg\n"
                        "Delta y = %.10Lg\n\n", stop_msg, iterations, n, x, f_x, logl(1+x), divs, delta_x, delta_y);
                error(ERR_UNKNOWN, err_msg);
        }

		const char *format = "%-7lld %-15.6Le %-24.16Lg %-24.16Lg %-15d %s\n";
        printf(format, i, x, f_x, logl(1 + x), iterations, stop_msg);
        fprintf(file, format, i, x, f_x, logl(1 + x), iterations, stop_msg);

        x += delta_x;
    }

    fclose(file);
}