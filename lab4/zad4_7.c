#include <stdlib.h>
#include <stdio.h>
// #include <conio.h>
#pragma warning (disable: 4996)

char getch() {
	char c;
	int ret = scanf("%c", &c);

	if(ret != 1) {
		printf("\nBlad przy wczytaniu\n");
		return '_';
	}

	return c;
}

int main(int argc, char* argv[]) {
	// Get input data
	printf("Program do wczytywania znakow\n");

	while (1) {
		printf("Podaj znak (podaj 'e' aby zakonczyć): ");

		char c = getch();
		printf("\n");

		// Print input data
		printf("n = %c\n", c);

		if (c == 'e')
			break;

		// Do sth with c
	}

	printf("---------------------------------------------------------\n");
	return 0;
}
