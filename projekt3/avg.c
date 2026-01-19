// avg.c

#include <stdlib.h>


int id(int row_len, int row, int col) {
	return row_len * row + col;
}

double avg_vector(double *x, int m) {
    double sum = 0.0;
    for (int i = 0; i < m; i++)
        sum += x[i];
    return sum / m;
}

double avg_row(double *A, int n, int row) {
    double sum = 0.0;
    for (int col = 0; col < n; col++)
        sum += A[id(n, row, col)];
    return sum / n;
}

double avg_col(double *A, int n, int col) {
    double sum = 0.0;
    for (int row = 0; row < n; row++)
        sum += A[id(n, row, col)];
    return sum / n;
}

double avg_diag(double *A, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += A[id(n, i, i)];
    return sum / n;
}

double avg_below_diag(double *A, int n) {
    double sum = 0.0;
    int count = 0;
    for (int row = 1; row < n; row++) {
        for (int col = 0; col < row; col++) {
            sum += A[id(n, row, col)];
            count++;
        }
    }
    return sum / count;
}

double avg_second_diag(double *A, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += A[id(n, i, n - 1 - i)];
    return sum / n;
}
