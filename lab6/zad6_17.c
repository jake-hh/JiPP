#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256
#define MAX_LINES 200

char **read_file(const char *file_name, int *lines_count);
void write_file(const char *file_name, char **d, int lines_count);
int getNumber(const char *prompt, int min, int max);
char *getString(const char *prompt);
void insert_after(char **d, int *lines_count, char *line, int n);
void print_lines(char **d, int lines_count);


int main(int argc, char **argv) {
	printf("Program do wstawiania nowej linii za linią o wybranym numerze\n");

	if (argc != 2 && argc != 3) {
		printf("Zła liczba argumentów\n");
		exit(1);
	}

	/* Tekst w pamieci, tablica d - wskazniki do linii tekstu */
	int lines_count = 0;
	char **d = read_file(argv[1], &lines_count);

	printf("Ilosc linii: %d\n", lines_count);
	int n = getNumber("Podaj numer linii za którą wstawić nową linię", 1, lines_count) - 1;
	char *line = getString("Podaj zawartość nowej linii");

	print_lines(d, lines_count);

	printf("Inserting line\n");
	insert_after(d, &lines_count, line, n);

	print_lines(d, lines_count);

	if (argc != 3)
		printf("WARNING: Nie podano nazwy pliku wyjściowego, pomijam zapis\n");
	else
		write_file(argv[2], d, lines_count);
}


int getNumber(const char *prompt, int min, int max) {
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

char *getString(const char *prompt) {
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
	strcpy(str, buf);

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


void write_file(const char *file_name, char **d, int lines_count) {
	FILE *fd;

	if (!(fd = fopen(file_name, "w"))) {
		printf("Blad otwarcia zbioru\n");
		exit(7);
	}

	for (int i = 0; i < lines_count; i++) {
		fwrite(d[i], sizeof(char), strlen(d[i]), fd);
		fputc('\n', fd);
	}

	fclose(fd);
}


void print_lines(char **d, int lines_count) {
	printf("\n[zawartość tablicy]\n");

	for (int i = 0; i < lines_count; i++)
		printf("%d: %s\n", i + 1, d[i]);

	printf("\n");
}


void insert_after(char **d, int *lines_count, char *line, int n) {
	if (n >= MAX_LINES) {
		printf("Przekroczono ilość maksymalnych linii\n");
		exit(8);
	}

	for (int i = (*lines_count)++; i > n; i--)
		d[i+1] = d[i];

	d[n+1] = line;
}
