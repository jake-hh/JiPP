#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

extern void error(int, char *);
void argumenty(int, char **);


int main(int argc, char *argv[]) {
	FILE *fw, *fd;
	double **a, **b, **c, *x, *y, r;
	int i, j, k, n, m;

	// -- Open files & read sizes--
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki");

	fscanf(fd, "%d %d", &n, &m);
	if (n < 1) error(1, "n < 1");
	if (m < 1) error(1, "m < 1");

	// -- Dynamically allocate memory --
	// Matrix A
    if (!(a = (double**)malloc(n * sizeof(double*))))
		error(3, "malloc");

	for (int i = 0; i < n; i++)
		if (!(a[i] = (double*)malloc(m * sizeof(double))))
			error(3, "malloc");

	// Matrix B
    if (!(b = (double**)malloc(n * sizeof(double*))))
		error(3, "malloc");

	for (int i = 0; i < n; i++)
		if (!(b[i] = (double*)malloc(m * sizeof(double))))
			error(3, "malloc");

	// Matrix C
    if (!(c = (double**)malloc(n * sizeof(double*))))
		error(3, "malloc");

	for (int i = 0; i < n; i++)
		if (!(c[i] = (double*)malloc(m * sizeof(double))))
			error(3, "malloc");

	// Vector X
    if (!(x = (double*)malloc(m * sizeof(double))))
		error(3, "malloc");

	// Vector Y
    if (!(y = (double*)malloc(m * sizeof(double))))
		error(3, "malloc");

	// -- Read matrixes & vectors --
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			fscanf(fd, "%lf", &a[i][j]);

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			fscanf(fd, "%lf", &b[i][j]);

	for (i = 0; i < m; i++)
		fscanf(fd, "%lf", &x[i]);

	// -- Calculate matrix and vector
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			c[i][j] = a[i][j] + b[i][j];

	for (i = 0; i < n; i++) {
		r = 0;
		for (k = 0; k < m; k++)
			r += a[i][k] * x[k];

		y[i] = r;
	}

	// -- Write to file --
	fprintf(fw, "Macierz C\n")
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			fprintf(fw, "%lf ", c[i][j]);

		fprintf(fw, "\n");
	}

	fprintf(fw, "Wektor Y\n")
	for (i = 0; i < m; i++) {
		fprintf(fw, "%lf ", y[i]);
		if (!((i + 1) % 5))
			fprintf(fw, "\n");
	}

	// -- Free memory --
	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
	a = NULL;

	for (int i = 0; i < n; i++)
		free(b[i]);
	free(b);
	b = NULL;

	for (int i = 0; i < n; i++)
		free(c[i]);
	free(c);
	c = NULL;

	free(x);
	x = NULL;
	free(y);
	y = NULL;

	return 0;
}


void argumenty(int argc, char *argv[]) {
	int len;
	char *usage;
	if (argc != 3) {
		len = strlen(argv[0]) + 19;

		if (!(usage = (char*)malloc((unsigned)len * sizeof(char))))
			error(3, "tablica usage");

		strcpy(usage, argv[0]);
		strcat(usage, " file_in file_out");
		error(4, usage);
	}
}