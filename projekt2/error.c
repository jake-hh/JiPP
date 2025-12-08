#include <stdio.h>
#include <stdlib.h>
#define MAX_ERR 7

static const char *p[] = { "",
	"Zle dane",
	"Zła liczba argumentow",
	"Otwarcie pliku",
	"Pusty plik",
	"Brak pamieci",
	"Inny",
	"Nieznany"
};

void error(int nr, const char *str) {
	int k = nr >= MAX_ERR ? MAX_ERR : nr;

	fprintf(stderr, "Blad(%d) - %s: %s\n", nr, p[k], str);
	exit(nr);
}