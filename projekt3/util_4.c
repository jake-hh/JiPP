// util_4.c

#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable: 4996)

extern void error(int, const char *);
extern int id(int row_len, int row, int col);
extern double *DajWekt(int n);
extern void ZwrocWekt(double *we);


double *DajMac(int n, int m) {
	return DajWekt(n * m);
}

void ZwrocMac(double *ma) {
	ZwrocWekt(ma);
}

void CzytMac(FILE *fd, double *ma, int n, int m) {

	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			if (fscanf(fd, "%lf", &ma[id(n, r, c)]) != 1) {

				char *err = (char*)malloc((unsigned)64);
				sprintf(err, "element nr %d %d\n", r, c);
				ZwrocMac(ma);
				error(3, err);
			}
}

void PiszMac(FILE *fw, double *ma, int n, int m) {

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++)
			fprintf(fw, "%g ", ma[id(n, r, c)]);

		fprintf(fw, "\n");
	}
}