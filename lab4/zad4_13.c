#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

const char* filename = "lab4.txt";


int main(int argc, char* argv[]) {

	FILE* fp = NULL;

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Nie można otworzyć pliku %s\n", filename);
		return 1;
	}

	char c = '_';
	while (fscanf(fp, "%c", &c) != EOF) {
		printf("%c", c);
	}

	fclose(fp);
	fp = NULL;
	return 0;
}
