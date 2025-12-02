#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#define LL 20

FILE *fw, *fd;
void argumenty(int, char **);
extern void error(int, char *);

int main(int argc, char *argv[]) {

	double **a, b[LL][LL], c[LL][LL], x[LL], y[LL], r;
	int i, j, k, n, m;

	// Matrix A
    if (!(a = malloc(LL * sizeof(double*))))
		error(3, "malloc");

	for (int i = 0; i < LL; i++)
		if (!(a[i] = malloc(LL * sizeof(double))))
			error(3, "malloc");

	// // Matrix B
    // if (!**b = malloc(LL * sizeof(double*)))
	// 	error(3, "malloc");

	// for (int i = 0; i < LL; i++)
	// 	if (!*a[i] = malloc(LL * sizeof(double)))
	// 		error(3, "malloc");

	// // Matrix C
    // if (!**c = malloc(LL * sizeof(double*)))
	// 	error(3, "malloc");

	// for (int i = 0; i < LL; i++)
	// 	if (!*a[i] = malloc(LL * sizeof(double)))
	// 		error(3, "malloc");

	// // Vector X
    // if (!*x = malloc(LL * sizeof(double)))
	// 	error(3, "malloc");

	// // Vector Y
    // if (!*y = malloc(LL * sizeof(double)))
	// 	error(3, "malloc");


	// -- Open files --
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki");

	// -- Read matrix sizes --
	fscanf(fd, "%d %d", &n, &m);

	// -- Read matrixes --
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			fscanf(fd, "%lf", &a[i][j]);

	for (i = 0; i < m; i++)
		fscanf(fd, "%lf", &x[i]);

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			fscanf(fd, "%lf", &b[i][j]);

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			c[i][j] = a[i][j] + b[i][j];

	for (i = 0; i < n; i++) {
		r = 0;
		for (k = 0; k < m; k++)
			r += a[i][k] * x[k];

		y[i] = r;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			fprintf(fw, "%lf ", c[i][j]);

		fprintf(fw, "\n");
	}

	for (i = 0; i < n; i++) {
		fprintf(fw, "%lf ", y[i]);
		if (!((i + 1) % 5))
			fprintf(fw, "\n");
	}

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