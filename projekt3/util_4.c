#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable: 4996)

extern void error(int, const char *);


double *DajMac(int n, int m) {
	double *ma;

    if (!(ma = (double*)malloc(n * m * sizeof(double))))
		error(3, "malloc macierz");

	return ma;
}


void ZwrocMac(double *ma) {
	free(ma);
}


void CzytMac(FILE *fd, double **ma, int n, int m) {

	for (int i = 0; i < n * m; i++)

			if (fscanf(fd, "%lf", &ma[i]) != 1) {
				char *err = (char*)malloc((unsigned)25);
				sprintf(err, "element nr %d %d\n", i / n, i % m);
				error(5, err);
			}
}


void PiszMac(FILE *fw, double **ma, int n, int m) {
	for (int i = 0; i < n * m; i++) {
		fprintf(fw, "%g ", ma[i][j]);

		fprintf(fw, "\n");
	}
	fprintf(fw, "\n");
}