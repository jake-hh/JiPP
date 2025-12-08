#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h>
#pragma warning (disable: 4996)

#define FORMAT_UP	'g'
#define FORMAT_DOWN	'd'

#define MAX_LINE 256

extern void error(int nr, char *str);

char get_format_mode();
char *read_line(const char *filename);
char **split_words(char *text, int *wcount);
int map_words_len(char **words, int wcount, int *wlen);
void printc(char c, FILE *f);
void print_vertical_columns(const char *outfile, char **words, int wcount, char mode);
void free_words(char **words, int wcount);


int main(int argc, char **argv) {
	//setlocale(LC_ALL, "Polish_Poland.1250");

	if (argc != 3) {
        error(2, "nalezy podac plik wejsciowy i wyjsciowy");
	}

	char mode = get_format_mode();

    char *line = read_line(argv[1]);
    if (!line)
        error(6, "read_line zwrocilo NULL");

    int wcount = 0;
    char **words = split_words(line, &wcount);
    if (!words) {
		free(line); line = NULL;
        error(6, "split_words zwrocilo NULL");
	}

    free(line);
    line = NULL;

    print_vertical_columns(argv[2], words, wcount, mode);

    free_words(words, wcount);
    return 0;
}


char get_format_mode() {
	char c;

	printf("Program do formatowania tekstu\n");
	printf("Podaj typ formatowania ([g]ora / [d]ol): ");

	// Check if scanf has read 1 variable
	if (scanf("%c", &c) != 1) {
        error(1, "Blad przy wczytaniu, podaj char");
	}
	printf("\n");

	if (c != FORMAT_UP && c != FORMAT_DOWN) {
        error(1, "nalezy podac 'g' lub 'd'");
	}

	return c;
}


char *read_line(const char *filename) {

    FILE *f = fopen(filename, "r");
    if (!f) {
        error(3, filename);
	}

	// dynamically allocated
    char *buf = NULL;
    size_t cap = 0;
    ssize_t len = getline(&buf, &cap, f);
    fclose(f);

    if (len <= 0) {
        free(buf);
        error(4, filename);
    }

    if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

    return buf;
}


char **split_words(char *text, int *wcount) {
    int cap = 8, n = 0;

    char **words = malloc(cap * sizeof(char*));
    if (!words) {
        free(text);
        error(5, "malloc");
	}

    char *tok = strtok(text, " ");
    while (tok) {
        if (n == cap) {
            cap *= 2;

            char **tmp = realloc(words, cap * sizeof(char*));
            if (!tmp) {
                free(text);
                free_words(words, *wcount);
                error(5, "realloc");
			}

            words = tmp;
        }

        words[n] = strdup(tok);
        if (!words[n]) {
            free(text);
            free_words(words, *wcount);
            error(5, "strdup");
		}

        n++;
        tok = strtok(NULL, " ");
    }

    *wcount = n;
    return words;
}


int map_words_len(char **words, int wcount, int *wlen) {
    int max = 0;

    for (int i = 0; i < wcount; i++) {
        wlen[i] = strlen(words[i]);
        if (wlen[i] > max)
			max = wlen[i];
    }
    return max;
}


void printc(char c, FILE *f) {
    putchar(c);
    fputc(c, f);
}


void print_vertical_columns(const char *outfile, char **words, int wcount, char mode) {
    FILE *f = fopen(outfile, "w");
    if (!f) {
        free_words(words, wcount);
        error(3, outfile);
	}

    int *wlen = malloc(wcount * sizeof(int));
    if (!wlen) {
        free_words(words, wcount);
        error(5, "malloc");
	}

    int maxh = map_words_len(words, wcount, wlen);

    for (int r = 0; r < maxh; r++) {
        for (int c = 0; c < wcount; c++) {

            int d = maxh - wlen[c];
            char ch;

            if (mode == FORMAT_UP)
                ch = r < wlen[c] ? words[c][r] : ' ';
            else
                ch = r >= d ? words[c][r - d] : ' ';

            printc(ch, f);

            if (c < wcount - 1)
                printc(' ', f);
        }
        printc('\n', f);
    }

    fclose(f);
}


void free_words(char **words, int wcount) {
    for (int i = 0; i < wcount; i++) {
		free(words[i]);
        words[i] = NULL;
    }
    free(words);
    words = NULL;
}
