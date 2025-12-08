#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 6

static char *p[] = { "",
	"zle dane",
	"otwarcie pliku",
	"brak pamieci",
	"Usage:",
	"odczyt pliku"
	"nieznany",
};

void error(int nr, char *str) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}
