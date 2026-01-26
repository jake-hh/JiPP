
extern int get_integer(char *msg, int min, int max);


int fibonacci(int n) {
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;

	return fibonacci(n - 2) + fibonacci(n - 1);
}


int main() {
	int n = get_integer("Podaj wyraz ciągu fibonacciego");

	int f = fibonacci(n);
	printf("wartość ciągu fibonacciego: %d\n", f);
	return 0;
}
