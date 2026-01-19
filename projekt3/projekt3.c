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

double avg_calculate(double *A, int n, int l, int calc_mode) {
	if (n <= 0)
		error(5, "wymiar n macierzy musi być dodatni");

	if (l < 0 || l >= n)
		error(5, "l poza zakresem");

	switch (calc_mode) {
		case AVG_VECTOR:
			if (l != 1)
				error(5, "wysokość macierzy (wektor) musi być 1");
			return avg_vector(A, n);

		case AVG_MATRIX_ROW:
			return avg_row(A, n, l);

		case AVG_MATRIX_COL:
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

	// -- Calculate --
	double ar = avg_calculate(ma, n, 1, AVG_MATRIX_ROW);
	double ac = avg_calculate(ma, n, 2, AVG_MATRIX_COL);

	// printf("Suma elementów na przękątnych spełniającyhc warunki: %g\n", sum);
	printf("\nMacierz M(%dx%d)\n", n, n);
	PiszMac(stdout, ma, n, n);
	printf("\nWektor R(%d)\n", m);
	PiszWekt(stdout, r, m);


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