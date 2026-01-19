// util_1.c

#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 7

static char *p[] = { "",
	"Usage:",
	"otwarcie pliku",
	"odczyt pliku"
	"brak pamięci",
	"złe argumenty funkcji",
	"wprowadzono złe dane",
	"nieznany"
};

void error(int nr, char *str) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}
