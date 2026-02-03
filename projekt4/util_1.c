// util_1.c

#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 8

static char *p[] = { "",
	/* 1 */ "Usage:",
	/* 2 */ "Otwarcie pliku",
	/* 3 */ "Odczyt pliku",
	/* 4 */ "Brak pamięci",
	/* 5 */ "Złe argumenty funkcji",
	/* 6 */ "Wprowadzono złe dane",
	/* 7 */ "Zapis pliku",
	/* 8 */ "Nieznany"
};

void error(int nr, const char *str) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s: %s\n", nr, p[k], str);
	exit(nr);
}
