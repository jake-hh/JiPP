#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void error(int nr, const char *str);


char *copy_word(char *buf) {
	int len = strlen(buf);

	if (len < 2)
		len = 2;

	if (buf[len - 2] == '\r')
		buf[len - 2] = '\0';
	else
		buf[len -1] = '\0';

	char *str = (char*)malloc(len);
	if (!str)
		error(4, "malloc copy word");

	strcpy(str, buf);
	return str;
}


char *get_string(char *msg, int cap) {
	printf("%s (text): ", msg);

    char str[cap];

    if (!fgets(str, cap, stdin))
		error(6, "fgets");

	// str[strlen(str) - 1] = '\0';
    return copy_word(str);
}


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
