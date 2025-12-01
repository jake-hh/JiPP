#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

void hanoi(int n, char a, char b, char c);


int main(int argc, char* argv[]) {

	printf("Program do rozwiązywania Wieży Hanoi\n");

	hanoi(3, 'A', 'B', 'C');

	return 0;
}

void hanoi(int n, char a, char b, char c) {
	if (n <= 1) {
		if (n != 1) {
			printf("Liczba musi być dodatnią liczbą naturalną\n");
			exit(1);
		}
		else {
			printf("%c -> %c\n", a, b);
		}
	}
	else {
		hanoi(n-1, a, c, b);
		printf("%c -> %c\n", a, b);
		hanoi(n-1, c, b, a);
	}
}