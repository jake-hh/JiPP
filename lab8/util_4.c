// a b c d
#include <stdlib.h>
#include <stdio.h>


double **DajMac_1(int n, int m)

double **DajMac_2(int n, int m)


void ZwrocMac_1(double **ma, int n, int m)

void ZwrocMac_2(double **ma, int n, int m)


void CzytMac(FILE *fd, double **ma, int n, int m) {
	int i, j;
	char *err;

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (fscanf(fd, "%lf", &ma[i][j]) != 1)
				printf("blad - element nr %d %d\n", i, j);
}


void PiszMac(FILE *fw, double **ma, int n, int m)