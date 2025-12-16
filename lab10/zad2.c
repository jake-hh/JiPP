#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996 6387)

#define MAX_BUFOR 80

typedef struct stud {
	char* imie;
	char* nazwisko;
	int rok;
	char* adres;
	double stypendium;
	struct stud* n;
} STUDENT;


char *copy_word(char *buf) {
	int len = strlen(buf);

	if (len < 2)
		len = 2;

	if (buf[len - 2] == '\r')
		buf[len - 2] = '\0';
	else
		buf[len -1] = '\0';

	char *str = (char*)malloc(len);
	strcpy(str, buf);

	return str;
}

STUDENT *read_list1(FILE* plik) {
	STUDENT *head = NULL, *node = NULL, *prev = NULL;
	char bufor[MAX_BUFOR];

	while (fgets(bufor, MAX_BUFOR, plik)) {

		node = (STUDENT*)malloc(sizeof(STUDENT));
		if (head == NULL)
			head = node;
		else
			prev->n = node;
		node->n = NULL;

		node->imie = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->nazwisko = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->rok = atoi(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->adres = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->stypendium = atof(bufor);

		prev = node;
	}

	return head;
}


STUDENT* max_s1(STUDENT *head) {
	if (head == NULL)
		return NULL;

	STUDENT *s, *x;
	double max = head->stypendium;
	x = head;

	for (s = head; s != NULL; s = s->n) {
		if (s->stypendium > max) {
			max = s->stypendium;
			x = s;
		}
	}
	return x;
}


void dispList1(STUDENT *head) {
	if (head == NULL) {
		printf("Lista pusta");
		return;
	}

	for (STUDENT *s = head; s != NULL; s = s->n) {
		printf("%p next:%p\n", s, s->n);
		printf("%10s |%10s | %4d |%25s | %7.2lf\n", s->imie, s->nazwisko, s->rok, s->adres, s->stypendium);
	}
	printf("\n");
}


int main(){
	STUDENT* head = NULL;

	FILE* fd = fopen("dane.txt", "r");
	if (fd == NULL) {
		printf("Nie mogę otworzyć pliku dane.txt do odczytu!\n");
		exit(2);
	}
	head = read_list1(fd);

	dispList1(head);

	STUDENT* ms = max_s1(head);
	printf("Najwyzsze stypendium: %s %.2lf\n", ms->nazwisko, ms->stypendium);
	// addHeadList1();
	// addTailList1();
	// dispList1();
	// printf("dlugosc listy = %d\n", lenList1());
	// remHeadList1();
	// dispList1();
	// remTailList1();
	// dispList1();
}