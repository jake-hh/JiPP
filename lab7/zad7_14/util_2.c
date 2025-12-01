#include <stdlib.h>

extern void error(int nr, char *str) {


double *DajWekt(int n) {
	double *w = NULL;

	w = (double *)malloc((double)n * sizeof(double));

	if (!w) {
		error(3);
	}
}

void CzytWekt(FILE *fd, double *we, int n) {
	for (int i = 0; i < n; i++)
		fscanf(fd, "%lf", &we[i]);
}

void PiszWekt(FILE *fw, double *we, int n) {
	for (int i = 0; i < n; i++) {
		fprintf(fw, "%lf ", we[i]);

		if (!((i + 1) % 5))
			fprintf(fw, "\n");
	}
}