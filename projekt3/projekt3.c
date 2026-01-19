#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*	Napisz fukcję obiczającą średnią arytmetyczą współrzędnych wektora "x nalezy do R^m".
	Następnie przyjmując, ze dana macierz A o n wierszach i n kolumnach policz:
	1) średnią arytmetyczną elementów tej macierzy lezących w l-tym wierszu
	2) średnią arytemetyczną elementów tej macierzy lezących w l-tej kolumnie
	3) średnią arytemetyczną elementów tej macierzy lezących na głównej przekątnej
	4) średnią arytemetyczną elementów tej macierzy lezących pod przekątną
	5) średnią arytemetyczną elementów tej macierzy z drugiej przekątne

	Uwagi
	− Wszystkie tablice alokowane dynamicznie.
	− Dane czytamy z pliku.
	− Wyniki zapisujemy do pliku i wyświetlamy na monitorze.
	− Pełna obsługa błędów dla wszystkich funkcji (patrz plik util_1.cpp z laboratorium).
	− Program podzielony na kilka plików (co najmniej 2 pliki).
	− Macierz należy wczytać/zapamiętać jako tablicę jednowymiarową.
		W zależności od wybranej opcji funkcja realizuje wskazane zadanie.
		W argumentach funkcji możemy stosować parametry domyślne. */

extern void error(int, const char *);
extern int id(int row_len, int row, int col);
extern int get_integer(char *msg, int min, int max);

extern double *DajWekt(int n);
extern void ZwrocWekt(double *we);
extern void CzytWekt(FILE *fd, double *we, int n);
extern void PiszWekt(FILE *fd, double *we, int n);

extern double *DajMac(int n, int m);
extern void ZwrocMac(double *ma);
extern void CzytMac(FILE *fd, double *ma, int n, int m);
extern void PiszMac(FILE *fw, double *ma, int n, int m);

extern double avg_vector(double *x, int m);
extern double avg_row(double *A, int n, int row);
extern double avg_col(double *A, int n, int col);
extern double avg_diag(double *A, int n);
extern double avg_below_diag(double *A, int n);
extern double avg_second_diag(double *A, int n);

void argumenty(int, char **);


#define AVG_VECTOR					0
#define AVG_MATRIX_ROW				1
#define AVG_MATRIX_COL				2
#define AVG_MATRIX_DIAGONAL			3
#define AVG_MATRIX_BELOW_DIAGONAL	4
#define AVG_MATRIX_SECOND_DIAGONAL	5
#define EXIT						6
#define N_AVG						6

void check(int l, int n) {
	if (l < 0 || l >= n)
		error(5, "l poza zakresem");
}

double avg_calculate(double *A, int n, int l, int calc_mode) {
	if (n <= 0)
		error(5, "wymiar n macierzy musi być dodatni");

	switch (calc_mode) {
		case AVG_VECTOR:
			return avg_vector(A, n);

		case AVG_MATRIX_ROW:
			check(l, n);
			return avg_row(A, n, l);

		case AVG_MATRIX_COL:
			check(l, n);
			return avg_col(A, n, l);

		case AVG_MATRIX_DIAGONAL:
			return avg_diag(A, n);

		case AVG_MATRIX_BELOW_DIAGONAL:
			return avg_below_diag(A, n);

		case AVG_MATRIX_SECOND_DIAGONAL:
			return avg_second_diag(A, n);

		default:
			error(5, "tryb obliczania nieznany");
            return 0;
	}
}

void abc(double *ma, int n, double *r, int m) {
	printf("\n=== Rodzaj operacji ===\n"
		"0 - średnia współrzędnych wektora R\n"
		"1 - średnia elementów macierzy M leżących w l-tym wierzu\n"
		"2 - średnia elementów macierzy M leżących w l-tej kolumnie\n"
		"3 - średnia elementów macierzy M leżących na głównej przekątnej\n"
		"4 - średnia elementów macierzy M leżących pod główną przekątną\n"
		"5 - średnia elementów macierzy M leżących na drugiej przekątnej\n"
		"6 - koniec\n\n");

	do {
		double avg;
		int l = 0;
		int op = get_integer("Podaj numer operacji", 0, N_AVG);

		if (op == EXIT)
			return;

		else if (op == AVG_VECTOR)
			avg = avg_calculate(r, m, 0, op);

		else {
			if (op == AVG_MATRIX_ROW)
				l = get_integer("Podaj numer wiersza l", 1, n);

			if (op == AVG_MATRIX_COL)
				l = get_integer("Podaj numer kolumny l", 1, n);

			avg = avg_calculate(ma, n, l - 1, op);
		}

		printf("Średnia elementów: %g\n", avg);
	}
	while(1);
}

int main(int argc, char *argv[]) {
	FILE *fd;
	int n, m;

	// -- Open file & read data --
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");

	fscanf(fd, "%d %d", &n, &m);
	if (n < 1) error(1, "n < 1");
	if (m < 1) error(1, "m < 1");

	// -- Dynamically allocate memory --
	double *ma = DajMac(n, n);
	double *r = DajWekt(m);

	// -- Read matrix --
	CzytMac(fd, ma, n, n);
	CzytWekt(fd, r, m);

	printf("\nMacierz M(%dx%d)\n", n, n);
	PiszMac(stdout, ma, n, n);
	printf("\nWektor R(%d)\n", m);
	PiszWekt(stdout, r, m);

	// -- Calculate --
	abc(ma, n, r, m);

	// -- Free --
	ZwrocMac(ma);
	ZwrocWekt(r);
	return 0;
}


void argumenty(int argc, char *argv[]) {
	int len;
	char *usage;
	if (argc != 2) {
		len = strlen(argv[0]) + 19;

		if (!(usage = (char*)malloc((unsigned)len * sizeof(char))))
			error(3, "tablica usage");

		strcpy(usage, argv[0]);
		strcat(usage, " file_in");
		error(4, usage);
	}
}