#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFOR 80

// double linked list
typedef struct stud {
	char *imie;
	char *nazwisko;
	int rok;
	char *adres;
	double stypendium;
	struct stud *p;
	struct stud *n;
} STUDENT;

void error(char *msg) {
	fprintf(stderr, "error: %s\n", msg);
	exit(1);
}

char *copyWord(char *buf) {
	int len = strlen(buf);

	if (len < 2)
		len = 2;

	if (buf[len - 2] == '\r')
		buf[len - 2] = '\0';
	else
		buf[len -1] = '\0';

	char *str = (char*)malloc(len);
	if (!str)
		error("out of memory");

	strcpy(str, buf);
	return str;
}


STUDENT *readList(FILE* plik, int max_n) {
	STUDENT *head = NULL, *node = NULL, *prev = NULL;
	char bufor[MAX_BUFOR];


	for (int i = 0; i < max_n && fgets(bufor, MAX_BUFOR, plik); i++) {

		node = (STUDENT*)malloc(sizeof(STUDENT));
		if (!node)
			error("out of memory");

		if (!head)
			head = node;
		else
			prev->n = node;
		node->p = prev;
		node->n = NULL;

		node->imie = copyWord(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->nazwisko = copyWord(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->rok = atoi(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->adres = copyWord(bufor);

		if(!fgets(bufor, MAX_BUFOR, plik)) break;
		node->stypendium = atof(bufor);

		prev = node;
	}

	return head;
}


void free_s(STUDENT *s) {
	free(s->imie);
	free(s->nazwisko);
	free(s->adres);
	free(s);
}


STUDENT *max_s(STUDENT *head) {
	if (!head)
		error("pusta lista");

	STUDENT *s, *max;
	max = head;

	for (s = head; s; s = s->n)
		if (s->stypendium > max->stypendium)
			max = s;

	return max;
}


int lenList(STUDENT *head) {
	if (!head)
		return 0;

	STUDENT *s = head;
	int n = 1;

	while ((s = s->n)) n++;
	return n;
}


void dispList(STUDENT *head) {
	if (!head) {
		printf("Lista pusta\n");
		return;
	}

	for (STUDENT *s = head; s; s = s->n) {
		printf("prev:%p %p next:%p\n", s->p, s, s->n);
		printf("  %-10s| %-10s| %4d | %-25s| %7.2lf\n", s->imie, s->nazwisko, s->rok, s->adres, s->stypendium);
	}
	printf("dlugosc listy = %d\n\n", lenList(head));
}


STUDENT *addHeadList(STUDENT *head, STUDENT *new_s) {
	if (!new_s)
		error("pusty student");

	new_s->p = NULL;
	new_s->n = head;
	if (head)
		head->p = new_s;
	return new_s;
}


STUDENT *addTailList(STUDENT *head, STUDENT *new_s) {
	if (!new_s)
		error("pusty student");

	if (!head)
		return new_s;

	STUDENT *s = head;
	while (s->n)
		s = s->n;

	new_s->n = NULL;
	new_s->p = s;
	s->n = new_s;

	return head;
}


STUDENT *remHeadList(STUDENT *head) {
	if (!head)
		return NULL;

	STUDENT *new_h = head->n;
	free_s(head);
	if (new_h)
		new_h->p = NULL;
	return new_h;
}


STUDENT *remTailList(STUDENT *head) {
	if (!head)
		return NULL;

	STUDENT *s = head;
	while (s->n)
		s = s->n;

	if (s->p) {
		s->p->n = NULL;
		free_s(s);
		return head;
	}
	else {
		free_s(s);
		return NULL;
	}
}


int main(){
	FILE *fd = fopen("dane.txt", "r");
	if (!fd)
		error("Nie mogę otworzyć pliku dane.txt do odczytu!");

	STUDENT *head = readList(fd, 2);
	dispList(head);

	STUDENT *ms = max_s(head);
	printf("Najwyzsze stypendium: %s %.2lf\n\n", ms->nazwisko, ms->stypendium);

	STUDENT *s = readList(fd, 1);
	head = addHeadList(head, s);
	dispList(head);

	s = readList(fd, 1);
	head = addTailList(head, s);
	dispList(head);

	head = remHeadList(head);
	dispList(head);

	// head = remHeadList(head);
	head = remTailList(head);
	dispList(head);

	// head = remHeadList(head);
	head = remTailList(head);
	dispList(head);

	// head = remHeadList(head);
	head = remTailList(head);
	dispList(head);

	// head = remHeadList(head);
	head = remTailList(head);
	dispList(head);
}