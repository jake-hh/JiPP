#include <float.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FILENAME "data.txt"

#define ERR_PROG_CALL	1
#define ERR_USER_INPUT	2
#define ERR_FILE_OPEN	3
#define ERR_UNKNOWN		4

extern void error(int nr, char *msg);
void clear_stdin();
void print_table(long double a, long double b, long double c, long n, long double delta_x, long double delta_y, int m);

enum STOP_REASON {
	UNKNOWN,
	MAX_N,
	MAX_PRECISION,
	BOTH_MAX
};


long double ff(long double a, long double x, long double delta_y, int m, int *stop_res, int *iterations) {
    int i = 0;              // iteration
    long double y = 1;
    long double nom_base = x * logl(a);
    long double element = 1;

    do {
        //a^x     //                1/1 + (xlna)^1/1! + (xlna)^2/2! + (xlna)^3/3! + ...
        element *= nom_base;
        element /= ++i;
        y += element;
    }
	while (fabs(element) > delta_y && i < m);

    if (fabs(element) <= delta_y)
        *stop_res = MAX_PRECISION;

    if (i >= m)
        *stop_res = MAX_N;

    if (i >= m && fabs(element) <= delta_y)
        *stop_res = BOTH_MAX;

    *iterations = i;
    return y;
}


int main() {
    printf("Program do tablicowania funkcji 𝑦 = 𝑓(𝑥)\n"
        "we wszystkich punktach podziału na 𝑛 części przedziału [b, c].\n"
        "Funkcja 𝑓 dana jest w postaci rozwinięcia w szereg potęgowy i w postaci wzoru analitycznego.\n"
        "Sumuj co najwyżej 𝑀 wyrazów szeregu.\n\n");

    printf("𝑓(𝑥) = 𝑎^𝑥, ∣𝑥∣ < ∞\n\n");

	long double a;
    printf("Podaj podstawę potęgi 𝑎 > 0: ");
    fflush(stdin);
    if (scanf("%Lf", &a) != 1 || a <= 0)
        error(ERR_USER_INPUT, "");
    clear_stdin();

    printf("\nx ∈ [b, c]\n\n");

	long double b;
    printf("Podaj początek zakresu ∣b∣ < ∞: ");
    fflush(stdin);
    if (scanf("%Lf", &b) != 1)
        error(ERR_USER_INPUT, "");
    clear_stdin();


	long double c;
    printf("Podaj koniec zakresu c ∈ (b, ∞): ");
    if (scanf("%Lf", &c) != 1 || c <= b)
        error(ERR_USER_INPUT, "");
    clear_stdin();


    long n;
    printf("Podaj liczbę przedziałów 𝑛 ≥ 2 ∧ 𝑛 ∈ ℤ: ");
    if (scanf("%ld", &n) != 1 || n < 2)
        error(ERR_USER_INPUT, "");
    clear_stdin();


    long double delta_x;
    printf("\nObliczam Δx = (c - b) / 𝑛\n");
    if ((c - b) / (long double) n < 1e-14)
        error(ERR_USER_INPUT, "Zbyt gęsty podział dla zadanego zakresu");
    delta_x = (c - b) / (long double) n;
    printf("Δx = %Lg\n\n", delta_x);


	long double delta_y;
    printf("Podaj dokładność elementów przy obliczaniu szeregu 𝜀 > 1e-14: ");
    if (scanf("%Lf", &delta_y) != 1 || delta_y < 1e-14)
        error(ERR_USER_INPUT, "");
    clear_stdin();


    int m;
    printf("Podaj maksymalną ilość iteracji 𝑀 ≥ 1 ∧ 𝑀 ∈ ℤ: ");
    if (scanf("%d", &m) != 1 || m < 1)
        error(ERR_USER_INPUT, "");
    clear_stdin();


	print_table(a, b, c, n, delta_x, delta_y, m);
}


void clear_stdin() {
    while (getchar() != '\n');
}


void print_table(long double a, long double b, long double c, long n, long double delta_x, long double delta_y, int m) {

    FILE *file = fopen(FILENAME, "w");
    if (!file)
        error(ERR_FILE_OPEN, FILENAME);

	//const char *header = "Krok\t\tx\t\t\t\tf_szereg(x)\t\t\tf_analityczna(x)\t\tliczba wyrazów\t\tPowód zatrzymania\n";
    const char *header = "%-7s %-15s %-24s %-24s %-15s  %s\n";
    printf(header, "krok", "x", "f_szereg(x)", "f_analit(x)", "liczba wyrazów", "Powód zatrzymania");
    fprintf(file, header, "krok", "x", "f_szereg(x)", "f_analit(x)", "liczba wyrazów", "Powód zatrzymania");

    long double x = b;

    for (long long i = 1; i <= n + 1; i++) {
        int stop_res = UNKNOWN;
        int iterations = 0;
        char *stop_msg;

        long double f_x = ff(a, x, delta_y, m, &stop_res, &iterations);

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
                        "m = %d\n"
                        "x = %.10Lg\n"
                        "F(x) = %.10Lg\t->\tln(1+x) = %.10Lg\n"
                        "n = %ld\n"
                        "Delta x = %.10Lg\n"
                        "Delta y = %.10Lg\n\n", stop_msg, iterations, m, x, f_x, powl(a, x), n, delta_x, delta_y);
                error(ERR_UNKNOWN, err_msg);
        }

		const char *format = "%-7lld %-15.6Le %-24.16Lg %-24.16Lg %-15d %s\n";
        printf(format, i, x, f_x, powl(a, x), iterations, stop_msg);
        fprintf(file, format, i, x, f_x, powl(a, x), iterations, stop_msg);

        x += delta_x;
    }

    fclose(file);
}