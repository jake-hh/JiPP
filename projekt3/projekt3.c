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
void ask_n_calculate(char * file_out_name, double *ma, int n, double *r, int m);
double avg_calculate(int calc_mode, double *A, int n, int l);  // l = 0


#define AVG_VECTOR					0
#define AVG_MATRIX_ROW				1
#define AVG_MATRIX_COL				2
#define AVG_MATRIX_DIAGONAL			3
#define AVG_MATRIX_BELOW_DIAGONAL	4
#define AVG_MATRIX_SECOND_DIAGONAL	5
#define EXIT						6
#define N_AVG						6

const char *AVG_MODE_NAME[] = {
	/* 0 */ "średnia współrzędnych wektora R",
	/* 1 */ "średnia elementów macierzy M leżących w l-tym wierzu",
	/* 2 */ "średnia elementów macierzy M leżących w l-tej kolumnie",
	/* 3 */ "średnia elementów macierzy M leżących na głównej przekątnej",
	/* 4 */ "średnia elementów macierzy M leżących pod główną przekątną",
	/* 5 */ "średnia elementów macierzy M leżących na drugiej przekątnej"
};


int main(int argc, char *argv[]) {
	FILE *f_in;
	int n, m;

	// -- Open file & read data --
	argumenty(argc, argv);
	if (!(f_in = fopen(argv[1], "r")))
		error(2, "dane");

	if (fscanf(f_in, "%d %d", &n, &m) != 2)
		error(3, "odczyt n i m");
	if (n < 1)
		error(3, "n < 1");
	if (m < 1)
		error(3, "m < 1");

	// -- Dynamically allocate memory --
	double *ma = DajMac(n, n);
	double *r = DajWekt(m);

	// -- Read matrix --
	CzytMac(f_in, ma, n, n);
	CzytWekt(f_in, r, m);
	fclose(f_in);

	printf("\nMacierz M(%dx%d)\n", n, n);
	PiszMac(stdout, ma, n, n);
	printf("\nWektor R(%d)\n", m);
	PiszWekt(stdout, r, m);

	// -- Calculate --
	ask_n_calculate(argv[2], ma, n, r, m);

	// -- Free --
	ZwrocMac(ma);
	ZwrocWekt(r);
	return 0;
}


void argumenty(int argc, char *argv[]) {
	int len;
	char *usage;
	if (argc != 3) {
		len = strlen(argv[0]) + 19;

		if (!(usage = (char*)malloc((unsigned)len * sizeof(char))))
			error(4, "tablica usage");

		strcpy(usage, argv[0]);
		strcat(usage, " file_in file_out");
		error(1, usage);
	}
}

void ask_n_calculate(char * file_out_name, double *ma, int n, double *r, int m) {
	FILE *f_out;
	if (!(f_out = fopen(file_out_name, "w"))) {
		ZwrocMac(ma);
		ZwrocWekt(r);
		error(2, file_out_name);
	}

	printf("\n=== Rodzaj operacji ===\n");
	for (int i = 0; i < N_AVG; i++)
		printf("%d - %s\n", i, AVG_MODE_NAME[i]);
	printf("6 - koniec\n\n");

	while(1) {
		double avg;
		int l = 0;
		int op = get_integer("Podaj numer operacji", 0, N_AVG);

		if (op == EXIT) {
			fclose(f_out);
			return;
		}

		else if (op == AVG_VECTOR)
			avg = avg_calculate(op, r, m, 0);

		else {
			if (op == AVG_MATRIX_ROW)
				l = get_integer("Podaj numer wiersza l", 1, n);

			if (op == AVG_MATRIX_COL)
				l = get_integer("Podaj numer kolumny l", 1, n);

			avg = avg_calculate(op, ma, n, l - 1);
		}

		printf("%s: %g\n", AVG_MODE_NAME[op], avg);
		fprintf(f_out, "%s: %g\n", AVG_MODE_NAME[op], avg);
	}
}

double avg_calculate(int calc_mode, double *A, int n, int l) {	// l = 0
	if (n <= 0) {
		free(A);
		error(5, "wymiar n macierzy musi być dodatni");
	}

	switch (calc_mode) {
		case AVG_VECTOR:
			return avg_vector(A, n);

		case AVG_MATRIX_ROW:
			if (l < 0 || l >= n) {
				free(A);
				error(5, "l poza zakresem");
			}
			return avg_row(A, n, l);

		case AVG_MATRIX_COL:
			if (l < 0 || l >= n) {
				free(A);
				error(5, "l poza zakresem");
			}
			return avg_col(A, n, l);

		case AVG_MATRIX_DIAGONAL:
			return avg_diag(A, n);

		case AVG_MATRIX_BELOW_DIAGONAL:
			return avg_below_diag(A, n);

		case AVG_MATRIX_SECOND_DIAGONAL:
			return avg_second_diag(A, n);

		default:
			free(A);
			error(5, "tryb obliczania nieznany");
            return 0;
	}
}
