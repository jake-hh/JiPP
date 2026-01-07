#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFOR 80

struct liczba8 {
	__int8_t a;
	__int8_t b;
};

union liczba16 {
	struct liczba8 jeden;
	__int16_t dwa;
};

/*
	Adres:   +0     +1
	Little:  12     34
	Big:     34     12
*/

int main() {
	union liczba16 u;
	u.jeden.a = 0x12;
	u.jeden.b = 0x34;

	printf("u.jeden.a: %i (0x%x)\n", u.jeden.a, u.jeden.a);
	printf("u.jeden.b: %i (0x%x)\n", u.jeden.b, u.jeden.b);
	printf("u.jeden.b: %i (0x%x)\n", u.dwa, u.dwa);

	return 0;
}