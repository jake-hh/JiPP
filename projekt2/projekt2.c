#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning (disable: 4996)

#define FORMAT_UP	'g'
#define FORMAT_DOWN	'd'

#define MAX_LINE 256

#define INPUT_FILE "file.txt"
// #define OUTPUT_FILE


char getFormatType() {
	char c;

	printf("Program do formatowania tekstu\n");
	printf("Podaj typ formatowania ([g]ora / [d]ol): ");

	// Check if scanf has read 1 variable
	if (scanf("%c", &c) != 1) {
		printf("\nBlad przy wczytaniu\n");
		exit(1);
	}
	printf("\n");

	if (c != FORMAT_UP && c != FORMAT_DOWN) {
		printf("Zly input\n");
		exit(2);
	}

	return c;
}

char *readFile() {
	char *text = (char *)malloc(sizeof(char) * MAX_LINE);
	FILE *file = NULL;

	if (!(file = fopen(INPUT_FILE, "r"))) {
		printf("Blad otwarcia pliku %s\n", INPUT_FILE);
		exit(3);
	}

	if (fgets(text, MAX_LINE, file) == (char*)NULL) {
		printf("Blad odczytu pliku %s\n", INPUT_FILE);
		exit(4);
	}

	fclose(file);
	file = NULL;
	return text;
}

int countWords(char *text) {
	if (strlen(text) == 0)
		return 0;

	int n = 1;
	for (int i = 0; text[i] != '\n'; i++)
		if (text[i] == ' ')
			n++;

	return n;
}

// char **splitWords(char *text) {
// 	char **words = (char **)malloc(sizeof(char *) * MAX_WORDS);
// }


int main(int argc, char* argv[]) {
	char type = getFormatType();
	char *text_str = readFile();

	printf("format type: %c\ntext: %s\n", type, text_str);

	int n_words = countWords(text_str);

	printf("number of words: %i", n_words);

	return 0;
}