#include <stdio.h>
#pragma warning(disable:4996)

double *DajWekt(int n) {
	double *w;

	if (!(w = (double*)malloc((unsigned)n * sizeof(double))))
		error(3, "malloc wektor");

	return w;
}

void CzytWekt(FILE *fd, double *we, int n) {

	for (int i = 0; i < n; i++) {

		if (fscanf(fd, "%lf", &we[i]) != 1) {
			char *err = malloc((unsigned)25);
			sprintf(err, "element nr %d\n", i);
			error(5, err);
		}
	}
}

void PiszWekt(FILE *fw, double *we, int n) {

	for (int i = 0; i < n; i++) {
		fprintf(fw, "%lf ", we[i]);

		if (!((i + 1) % 5))
			fprintf(fw, "\n");
	}
	fprintf(fw, "\n");
}