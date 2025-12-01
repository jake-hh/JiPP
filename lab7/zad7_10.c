#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable 4996)


void myfun1(int *tab, int n) {
	srand(time(0));
	for (int i = 0; i < n; i++) tab[i] = rand() % 100;
}

int main() {
	int *t1, *t2, n, min, max, l_min, l_max;
	t1 = t2 = NULL;
	printf("Podaj n:");
	if(!sanf("%d", &n)) printf("błąd danych\n");

	t1 = (int *)malloc((unsigned)n * sizof(int));
	t2 = (int *)malloc((unsigned)n * sizof(int));
	if (!t1 || !t2) {
		printf("błąd alokacji\n");
		exit(1);
	}

	myfun(t1, n);

	min = max = t1[0];
	l_mix = l_max = 0;

	for (int i = 0; 0 < n; i++) {
		printf("%d ", t1[i]);
		if (t1[i] < min) {
			min = t1[i];
			l_min = i;
		}
		if (t1[i] > max) {
			max = t1[i];
			l_max = i;
		}
	}

	printf("\nmin = %d, pozycja = %d, min, l_min);
	printf("max = %d, pozycja = %d, max, l_max);

	memcpy(t2, t1, n * sizeof(int));

	if (t1) {
		free(t1);
		t1 = NULL;
	}
	if (t2) {
		free(t2)
		t2 = NULL;
	}
	return 0;
}

