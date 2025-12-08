#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

extern void error(int, char *);

extern double *DajWekt(int n);
extern void CzytWekt(FILE *fd, double *we, int n);
extern void PiszWekt(FILE *fw, double *we, int n);

extern double **DajMac_1(int n, int m);
extern double *DajMac_2(int n, int m);
extern void ZwrocMac_1(double **ma, int n);
extern void ZwrocMac_2(double *ma);
extern void CzytMac(FILE *fd, double **ma, int n, int m);
extern void PiszMac(FILE *fw, double **ma, int n, int m);

extern void DodMac(double **ma1, double **ma2, double **ma3, int n, int m);
extern void Mac_x_Wekt(double **ma, double *we, double *wy, int n, int m);
extern void Mac_x_Mac(double **x, double **y, double **z, int n, int m, int p);

void argumenty(int, char **);


int main(int argc, char *argv[]) {
	FILE *fw, *fd;
	double **a, **b, **c, *x, *y;
	int n, m;

	// -- Open files & read sizes--
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki");

	fscanf(fd, "%d %d", &n, &m);
	if (n < 1) error(1, "n < 1");
	if (m < 1) error(1, "m < 1");

	// -- Dynamically allocate memory --
	// Matrix A, B, C
	a = DajMac_1(n, m);
	b = DajMac_1(n, m);
	c = DajMac_1(n, m);

	// Vectors x, y
	x = DajWekt(m);
	y = DajWekt(m);

	// -- Read matrixes & vectors --
	CzytMac(fd, a, n, m);
	CzytMac(fd, b, n, m);
	CzytWekt(fd, x, m);

	// -- Calculate matrix and vector
	DodMac(a, b, c, n, m);
	Mac_x_Wekt(a, x, y, n, m);

	// -- Write to file --
	printf("Macierz C\n");
	PiszMac(stdout, c, n, m);
	fprintf(fw, "Macierz C\n");
	PiszMac(fw, c, n, m);

	printf("Wektor Y\n");
	PiszWekt(stdout, y, m);
	fprintf(fw, "Wektor Y\n");
	PiszWekt(fw, y, m);

	ZwrocMac_1(a, n);
	ZwrocMac_1(b, n);
	ZwrocMac_1(c, n);
	ZwrocMac_2(x);
	ZwrocMac_2(y);

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