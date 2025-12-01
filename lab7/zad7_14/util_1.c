#include <stdio.h>
#define MAX_ERR 5

static char *p[] = { "",
	"zle dane",
	"otwarcie pliku",
	"brak pamieci",
	"usage : ",
	"nieznany",
};

void error(int nr, char *str) {
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}