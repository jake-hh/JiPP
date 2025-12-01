#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

#define INPUT_FILE "file.txt"


/* ---------------- READ LINE ---------------- */
char *read_line(const char *filename) {

    FILE *f = fopen(filename, "r");
    if (!f) {
		perror("open input");
		return NULL;
	}

	// dynamically allocated
    char *buf = NULL;
    size_t cap = 0;
    ssize_t len = getline(&buf, &cap, f);
    fclose(f);

    if (len <= 0) {
        free(buf);
        fprintf(stderr, "No data in file\n");
        return NULL;
    }

    if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

    return buf;
}

/* ---------------- SPLIT INTO WORDS ---------------- */
char **split_words(char *text, int *count) {
    int cap = 4, n = 0;

    char **words = malloc(cap * sizeof(char*));
    if (!words) {
		perror("malloc");
		return NULL;
	}

    char *tok = strtok(text, " ");
    while (tok) {
        if (n == cap) {
            cap *= 2;

            char **tmp = realloc(words, cap * sizeof(char*));
            if (!tmp) {
				perror("realloc");
				return NULL;
			}

            words = tmp;
        }

        words[n] = strdup(tok);
        if (!words[n]) {
			perror("strdup");
			return NULL;
		}

        n++;
        tok = strtok(NULL, " ");
    }

    *count = n;
    return words;
}

/* ---------------- MAX WORD LENGTH ---------------- */
int find_max_word_len(char **words, int count) {
    int max = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        if (len > max)
			max = len;
    }
    return max;
}

/* ---------------- PRINT VERTICAL COLUMNS ---------------- */
int print_vertical_columns(const char *outfile, char **words, int count) {
    FILE *f = fopen(outfile, "w");
    if (!f) {
		perror("open output");
		return 0;
	}

    int maxh = find_max_word_len(words, count);

    for (int r = 0; r < maxh; r++) {
        for (int c = 0; c < count; c++) {

            char ch = (r < (int)strlen(words[c])) ? words[c][r] : ' ';

            putchar(ch);
            fputc(ch, f);

            if (c < count - 1) {
                putchar(' ');
                fputc(' ', f);
            }
        }
        putchar('\n');
        fputc('\n', f);
    }

    fclose(f);
    return 1;
}

/* ---------------- FREE WORDS ---------------- */
void free_words(char **words, int count) {
    for (int i = 0; i < count; i++)
		free(words[i]);
    free(words);
}

/* ---------------- MAIN ---------------- */
int main() {
    char *line = read_line(INPUT_FILE);
    if (!line)
		return 1;

    int count = 0;

    char **words = split_words(line, &count);
    if (!words) {
		free(line);
		return 1;
	}

    if (!print_vertical_columns("output.txt", words, count)) {
        free_words(words, count);
        free(line);
        return 1;
    }

    free_words(words, count);
    free(line);
    return 0;
}
