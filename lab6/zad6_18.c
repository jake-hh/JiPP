#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h>

#define MAX_CHARS 256
#define MAX_LINES 200
#define SEPARATOR ':'

char **read_file(const char *file_name, int *lines_count);
int get_number(const char *prompt, int min, int max);
void print_lines(char **d, int lines_count);
int find_word_in_line(char *te, int wanted_pos, int *cur_pos);
int find_word_in_lines(char **te, int wanted_pos);


int main(int argc, char **argv) {
	// setlocale(LC_ALL, "Polish_Poland.1250");
	printf("Program do wstawiania nowej linii za linią o wybranym numerze\n");

	if (argc != 2) {
		printf("Zła liczba argumentów\n");
		exit(1);
	}

	/* Tekst w pamieci, tablica d - wskazniki do linii tekstu */
	int lines_count = 0;
	char **d = read_file(argv[1], &lines_count);

	printf("Ilosc linii: %d\n", lines_count);
	int n = get_number("Podaj numer slowa", 1, 1000000) - 1;

	print_lines(d, lines_count);

	printf("Searching for word\n");
	find_word_in_lines(d, n);

	// free memeory
	for (int i = 0; i < lines_count; i++) {
		free(d[i]);
		d[i] = NULL;
	}
	free(d);
	d = NULL;
}


int get_number(const char *prompt, int min, int max) {
	printf("%s: ", prompt);
	int n = 0;

	if (scanf("%u", &n) != 1) {
		printf("Blad przy wczytaniu\n");
		exit(5);
	}

	if (n < min || n > max) {
		printf("Przekroczono zakres\n");
		exit(6);
	}

	// flush stdin
	int c; while ((c = getchar()) != '\n' && c != EOF) {}

	return n;
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
			exit(4);
		}

		strcpy(d[i], bufor);
		i++;
	}

	d[i] = (char *)0; //znacznik końca tablicy wskaźników
	*lines_count = i;
	fclose(fd);

	return d;
}


void print_lines(char **d, int lines_count) {
	printf("\n[zawartość tablicy]\n");

	for (int i = 0; i < lines_count; i++)
		printf("%d: %s\n", i + 1, d[i]);

	printf("\n");
}


int find_word_in_line(char *te, int wanted_pos, int *cur_pos) {
	char p, b = SEPARATOR;

	while (p = b, b = *te++) {
		if (b != SEPARATOR && p == SEPARATOR) {
			// found word
			if (*cur_pos == wanted_pos) {
				printf("found word: ");
				while (b != SEPARATOR && b != '\0') {
					printf("%c", b);
					b = *te++;
				}
				printf("\n");
				return 1;
			}
			(*cur_pos)++;
		}
	}

	return 0;
}


int find_word_in_lines(char **te, int wanted_pos) {
	int found = 0, cur_pos = 0;

	while (*te && !found)
		found = find_word_in_line(*te++, wanted_pos, &cur_pos);

	if (!found)
		printf("Error: Word not found! The file has only %d words\n", cur_pos);

	return found;
}
