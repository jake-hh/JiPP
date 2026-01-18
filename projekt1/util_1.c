#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 4

static char *p[] = { "",
	"Usage:",
	"błędne dane",
	"otwarcie pliku",
	"nieznany"
};

void error(int nr, char *msg) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], msg);
	exit(nr);
}
