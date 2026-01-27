#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE_NAME "dane.txt"

#define MAX_BUFFOR 256

// single linked list
typedef struct stud {
	char *name;
	char *surname;
	int year;
	struct stud *next;
} STUDENT;

extern void error(int nr, const char *str);
extern char *copy_word(char *buf);
extern char *get_string(char *msg, int cap);
extern int get_integer(char *msg, int min, int max);


STUDENT *read_list(FILE* plik) {
	STUDENT *head = NULL, *node = NULL, *prev = NULL;
	char bufor[MAX_BUFFOR];

	while (fgets(bufor, MAX_BUFFOR, plik)) {

		node = (STUDENT*)malloc(sizeof(STUDENT));
		if (!node)
			error(4, "malloc student");

		if (!head)
			head = node;
		else
			prev->next = node;
		node->next = NULL;

		node->name = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, plik)) break;
		node->surname = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, plik)) break;
		node->year = atoi(bufor);

		prev = node;
	}

	return head;
}


STUDENT *get_student() {
	printf("\nDodawanie studenta\n");
	STUDENT *node = (STUDENT*)malloc(sizeof(STUDENT));
	if (!node)
		error(4, "malloc student");

	node->name = get_string("Enter name", MAX_BUFFOR);
	node->surname = get_string("Enter surname", MAX_BUFFOR);
	node->year = get_integer("Enter year", 2000, 2100);
	return node;
}


STUDENT *find_student_by_surname(STUDENT *head, char *surname) {
	// while (head && strcmp(head->surname, surname))
	while (head && !strstr(head->surname, surname))
		head = head->next;

	return head;
}


int length_list(STUDENT *head) {
	int len = 0;

	while (head) {
		head = head->next;
		len++;
	}

	return len;
}


void display_student(STUDENT *s) {
	if (s)
		printf("  %-10s| %-10s| %4d\n", s->name, s->surname, s->year);
	else
		printf("  NULL\n");
}


void display_list(STUDENT *head) {
	if (!head) {
		printf("Lista pusta\n");
		return;
	}
	else {
		printf("\n[Lista]\n");
	}

	for (STUDENT *s = head; s; s = s->next) {
		printf("%p next:%p\n", s, s->next);
		display_student(s);
	}
	printf("dlugosc listy = %d\n\n", length_list(head));
}


STUDENT *push_student(STUDENT *head, STUDENT *new_s) {
	if (!new_s)
		error(5, "pusty student");

	new_s->next = head;
	return new_s;
}


STUDENT *pop_student(STUDENT **head) {
	if (!head)
		error(5, "ptr to ptr to head is null");

	if (!*head)
		return NULL;

	STUDENT *s = *head;
	*head = (*head)->next;
	s->next = NULL;
	return s;
}


void free_student(STUDENT *s) {
	free(s->name);
	free(s->surname);
	free(s);
}


void free_list(STUDENT *head) {
	while (head)
		free_student(pop_student(&head));
}


int main(){
	FILE *fd = fopen(DATA_FILE_NAME, "r");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku z danymi do odczytu!");

	STUDENT *head = read_list(fd);
	display_list(head);

	STUDENT *found = find_student_by_surname(head, "Krupi");

	printf("Znaleziono:\n");
	display_student(found);

	head = push_student(head, get_student());
	display_list(head);

	STUDENT *s = pop_student(&head);
	printf("Usunięto:\n");
	display_student(s);
	free_student(s);
	display_list(head);

	fclose(fd);
	return 0;
}