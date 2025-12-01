
void DodWekt(double *w1, double *w2, double *w3, int n){
	w1[n] = w2[n] + w3[n];
}

double IloczynSkal(double *w1, double *w2, int n) {
	return w1[n] * w1[n];
}

double MaxElem(double *w, int n, double max) {
	return w[n] > max ? w[n] : max;
}