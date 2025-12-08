#include <stdlib.h>
#include <stdio.h>

extern void error(int, char *);


double **DajMac_1(int n, int m) {
	double **ma;

    if (!(ma = (double**)malloc(n * sizeof(double*))))
		error(3, "malloc macierz");

	for (int i = 0; i < n; i++)
		if (!(ma[i] = (double*)malloc(m * sizeof(double))))
			error(3, "malloc macierz");

	return ma;
}

double *DajMac_2(int n, int m) {
	double *ma;

    if (!(ma = (double*)malloc(n * m * sizeof(double))))
		error(3, "malloc macierz");

	return ma;
}


void ZwrocMac_1(double **ma, int n) {
	for (int i = 0; i < n; i++)
		free(ma[i]);
	free(ma);
}

void ZwrocMac_2(double *ma) {
	free(ma);
}


void CzytMac(FILE *fd, double **ma, int n, int m) {

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)

			if (fscanf(fd, "%lf", &ma[i][j]) != 1) {
				char *err = malloc((unsigned)25);
				sprintf(err, "element nr %d %d\n", i, j);
				error(5, err);
			}
}


void PiszMac(FILE *fw, double **ma, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			fprintf(fw, "%g ", ma[i][j]);

		fprintf(fw, "\n");
	}
	fprintf(fw, "\n");
}