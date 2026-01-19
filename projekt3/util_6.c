// util_6.c

#include <stdio.h>

extern void error(int, const char *);


int get_natural_number(char *msg, int max) {
	// Get n
	int n = 0;
	printf("%s (0 - %d): ", msg, max);

	if (scanf("%i", &n) != 1)
		error(6, "Blad przy wczytaniu");

	// Check requirement
	if (n < 0) {
		error(6, "Liczba nie może być mniejsza od 0\n");
	}

	if (n > max)
		error(6, "Przekroczono zakres\n");

	return n;
}
