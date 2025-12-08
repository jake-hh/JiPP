
void DodWekt(double *w1, double *w2, double *w3, int n) {
	for (int i = 0; i < n; i++)
		w3[i] = w1[i] + w2[i];
}

double IloczynSkal(double *w1, double *w2, int n) {
	double is = 0;

	for (int i = 0; i < n; i++)
		is += w1[i] * w2[i];

	return is;
}

double MaxElem(double *w, int n) {
	double max;
	max = w[0];

	for (int i = 1; i < n; i++)
		max = w[i] > max ? w[i] : max;

	return max;
}
