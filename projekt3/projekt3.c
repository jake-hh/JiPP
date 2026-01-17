#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#pragma warning(disable: 4996)

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

extern double avg_calculate(double *A, int n, int l, int calc_mode);
extern void error(int, const char *);
extern int id(int row_len, int row, int col);

extern double **DajMac_1(int n, int m);
extern void ZwrocMac_1(double **ma, int n);
extern void CzytMac(FILE *fd, double **ma, int n, int m);

void argumenty(int, char **);


int main(int argc, char *argv[]) {
	//setlocale(LC_ALL, "Polish_Poland.1250");

	FILE *fd;
	double **ma, a, b, sum = 0;
	int n;

	// -- Open file & read data --
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");

	fscanf(fd, "%d %lf %lf", &n, &a, &b);
	if (n < 1) error(1, "n < 1");

	// -- Dynamically allocate memory --
	ma = DajMac_1(n, n);

	// -- Read matrix --
	CzytMac(fd, ma, n, n);

	// -- Calculate --
	for (int i = 0; i < n; i++) {
		// glowna przekatna
		if (sin(ma[i][i]) >= 0)
			sum += ma[i][i];
		// druga przekatna
		if (sin(ma[i][n-1-i]) >= 0.5)
			sum += ma[i][n-1-i];
	}

	printf("Suma elementów na przękątnych spełniającyhc warunki: %g\n", sum);

	// -- Free --
	ZwrocMac_1(ma, n);
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