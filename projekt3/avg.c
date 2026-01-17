// avg.c

#include <stdlib.h>

extern int id(int row_len, int row, int col);

#define AVG_VECTOR					0
#define AVG_MATRIX_ROW				1
#define AVG_MATRIX_COL				2
#define AVG_MATRIX_DIAGONAL			3
#define AVG_MATRIX_BELOW_DIAGONAL	4
#define AVG_MATRIX_SECOND_DIAGONAL	5


double avg_calculate(double *A, int n, int l, int calc_mode) {
	if (n <= 0 || l <= 0)
		error(4, "wymiary macierzy muszą być dodatnie");

	switch (calc_mode) {
		case AVG_VECTOR:
			if (l != 1)
				error(4, "wysokość macierzy (wektor) musi być 1");
			return avg_vector(A, n);

		case AVG_MATRIX_ROW:
			return avg_row(A, n, l);

		case AVG_MATRIX_COL:
			return avg_col(A, n, l);

		case AVG_MATRIX_DIAGONAL:
			return avg_diag(A, n, l);

		case AVG_MATRIX_BELOW_DIAGONAL:
			return avg_below_diag(A, n, l);

		case AVG_MATRIX_SECOND_DIAGONAL:
			return avg_second_diag(A, n, l);

		default:
			error(4, "tryb obliczania nieznany";
	}
}


double avg_vector(double *x, int m) {
    double s = 0.0;
    for (int i = 0; i < m; i++)
        s += x[i];
    return s / m;
}

double avg_row(double *A, int n, int l) {
    double s = 0.0;
    for (int j = 0; j < n; j++)
        s += A[id(n, l, j)];
    return s / n;
}

double avg_col(double *A, int n, int l) {
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += A[id(n, i, l)];
    return s / n;
}

double avg_diag(double *A, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += A[id(n, i, i)];
    return s / n;
}

double avg_below_diag(double *A, int n) {
    double s = 0.0;
    int cnt = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++) {
            s += A[id(n, i, j)];
            cnt++;
        }
    return s / cnt;
}

double avg_second_diag(double *A, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += A[id(n, i, n - 1 - i)];
    return s / n;
}
