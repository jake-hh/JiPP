#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h>

#define MAX_CHARS 256
#define MAX_LINES 200

char **read_file(const char *file_name, int *lines_count);
char *get_str(const char *prompt);
void print_lines(char **d, int lines_count);
void print_matching_lines(char **d, int lines_count, const char *pattern);
int common_pattern_len(const char *a, const char *b);
// int contains(const char *str, const char *pattern);


int main(int argc, char **argv) {
	// setlocale(LLC_ALL, "Polish_Poland.1250");
	printf("Program do znajdowania pasujących linii\n");

	if (argc != 2) {
		printf("Zła liczba argumentów: podaj plik wejściowy\n");
		exit(1);
	}

	/* Tekst w pamieci, tablica d - wskazniki do linii tekstu */
	int lines_count = 0;
	char **d = read_file(argv[1], &lines_count);


	print_lines(d, lines_count);
	printf("Ilosc linii: %d\n", lines_count);

	char *pattern = get_str("Podaj pattern");

	//print_lines(d, lines_count);

	printf("Searching lines\n");
	print_matching_lines(d, lines_count, pattern);
}


char *get_str(const char *prompt) {
	printf("%s: ", prompt);

	char buf[MAX_CHARS];
	if (!fgets(buf, sizeof(char) * MAX_CHARS, stdin)) {
		printf("Blad przy wczytaniu\n");
		exit(5);
	}

	int len = strlen(buf);
	buf[len - 1] = '\0';

	char *str;
	if (!(str = (char*)malloc(sizeof(char) * len))) {

			printf("Brak pamieci\n");
			exit(4);
	}

	return str;
}


char **read_file(const char *file_name, int *lines_count) {
	FILE *fd;
	char **d, bufor[MAX_CHARS];
	int len, i, l;

	if (!(d = (char**)malloc(MAX_LINES))) {
			printf("Brak pamieci\n");
			exit(3);
	}

	if (!(fd = fopen(file_name, "r"))) {
		printf("Blad otwarcia zbioru\n");
		exit(2);
	}

	i = 0;
	l = 0;
	while (i < MAX_LINES && fgets(bufor, MAX_CHARS, fd)) {

		len = strlen(bufor);
		bufor[len - 1] = '\0';

		if (!(d[i] = (char*)malloc((unsigned)len))) {
			printf("Brak pamieci\n");
			exit(6);
		}

		strcpy(d[i], bufor);
		i++;
	}

	d[i] = (char *)0; //znacznik końca tablicy wskaźników
	*lines_count = i;
	fclose(fd);

	return d;
}


void print_matching_lines(char **d, int lines_count, const char *pattern) {
	int found = 0;

	for (int i = 0; i < lines_count; i++) {
		if (common_pattern_len(d[i], pattern) == strlen(pattern) - 1) {
			printf("%d: [match] %s\n", i, d[i]);
			found = 1;
		}
	}

	if (!found)
		printf("Nie znaleziono pasujących linii\n");
}


int common_pattern_len(const char *a, const char *b) {
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i]) i++;
    return i;
}


void print_lines(char **d, int lines_count) {
	printf("\n[zawartość tablicy]\n");

	for (int i = 0; i < lines_count; i++)
		printf("%d: %s\n", i + 1, d[i]);

	printf("\n");
}
