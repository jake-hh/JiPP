#include <stdlib.h>
#include <stdio.h>

extern void error(int, char *);


double **DajMac_1(int n, int m) {
	double **ma;

    if (!(ma = (double**)malloc(n * sizeof(double*))))
		error(3, "malloc");

	for (int i = 0; i < n; i++)
		if (!(ma[i] = (double*)malloc(m * sizeof(double))))
			error(3, "malloc");

	return ma;
}

double *DajMac_2(int n, int m) {
	double *ma;

    if (!(ma = (double*)malloc(n * m * sizeof(double))))
		error(3, "malloc");

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
	int i, j;
	char *err;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fscanf(fd, "%lf", &ma[i][j]) != 1)
				printf("blad - element nr %d %d\n", i, j);
}


void PiszMac(FILE *fw, double **ma, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			fprintf(fw, "%lf ", ma[i][j]);

		fprintf(fw, "\n");
	}
}