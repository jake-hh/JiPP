// util_6.c

#include <stdio.h>

extern void error(int, const char *);


int get_integer(char *msg, int min, int max) {
	// Get n
	int n = 0;
	printf("%s (%d - %d): ", msg, min, max);

	if (scanf("%i", &n) != 1)
		error(6, "Blad przy wczytaniu");

	// Check requirement
	if (n < min) {
		error(6, "Wartość poza minimum");
	}

	if (n > max)
		error(6, "Wartość poza maximum");

	return n;
}
