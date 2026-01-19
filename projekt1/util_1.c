#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 4

static char *p[] = { "",
	/* 1 */ "Usage:",
	/* 2 */ "Błędne dane",
	/* 3 */ "Otwarcie pliku",
	/* 4 */ "Nieznany"
};

void error(int nr, char *msg) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], msg);
	exit(nr);
}
