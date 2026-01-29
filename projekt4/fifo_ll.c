#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define DATA_FILE_NAME "dane.txt"

#define MAX_BUFFOR 256

// single linked list
typedef struct stud {
	char *name;
	char *surname;
	int year;
	struct stud *next;
} Student;

extern void error(int nr, const char *str);
extern char *copy_word(char *buf);
extern char *get_string(char *msg, int cap);
extern int get_integer(char *msg, int min, int max);


void print_menu(Student *head) {
	printf("\n[Menu]\n"
			"0 - Quit\n"
			"1 - Add student\n"
			"2 - Remove student\n"
			"3 - Find student by surname\n"
			"4 - Display list\n"
			"5 - Count students in list\n"
			"6 - Drop students list\n"
			"7 - Save to binary file\n");

	if (!head)
		printf("8 - Load from binary file\n"
				"9 - Load from text file\n");

	printf("\n");
}


int get_menu_size(Student *head) {
	return head ? NO_READ_MENU_SIZE : MENU_SIZE;
}


Student *get_student() {
	printf("\nDodawanie studenta\n");
	Student *node = (Student*)malloc(sizeof(Student));
	if (!node)
		error(4, "malloc student");

	node->name = get_string("Enter name", MAX_BUFFOR);
	node->surname = get_string("Enter surname", MAX_BUFFOR);
	node->year = get_integer("Enter year", 2000, 2100);
	return node;
}


Student *find_student_by_surname(Student *head, char *surname) {
	// while (head && strcmp(head->surname, surname))
	while (head && !strstr(head->surname, surname))
		head = head->next;

	return head;
}


int length_list(Student *head) {
	int len = 0;

	while (head) {
		head = head->next;
		len++;
	}

	return len;
}


void display_list_length(Student *head) {
	printf("dlugosc listy = %d\n\n", length_list(head));
}


void display_student(Student *s) {
	if (s)
		printf("  %-10s| %-10s| %4d\n", s->name, s->surname, s->year);
	else
		printf("  NULL\n");
}


void display_list(Student *head) {
	if (!head) {
		printf("Lista pusta\n");
		return;
	}
	else {
		printf("\n[Lista studentów]\n");
	}

	for (Student *s = head; s; s = s->next) {
		printf("%p next:%p\n", s, s->next);
		display_student(s);
	}
	display_list_length(head);
}


// --- wsadź element na początku ---
Student *push_student(Student *head, Student *new_s) {
	if (!new_s)
		error(5, "pusty student");

	new_s->next = head;
	return new_s;
}


// --- usuń ostatni element ---
Student *pop_student(Student **head) {
	if (!head)
		error(5, "ptr to ptr to head is null");

	if (!*head)
		return NULL;

	Student *s = *head;
	Student *prev = NULL;
	while (s->next) {
		prev = s;
		s = s->next;
	}

	if (prev)
		prev->next = NULL;
	else
		*head = NULL;

	return s;
}


Student *read_list() {
	FILE *fd = fopen(DATA_FILE_NAME, "r");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku z danymi do odczytu!");

	Student *head = NULL, *node = NULL;
	char bufor[MAX_BUFFOR];

	while (fgets(bufor, MAX_BUFFOR, fd)) {

		node = (Student*)malloc(sizeof(Student));
		if (!node)
			error(4, "malloc student");

		node->name = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, fd)) break;
		node->surname = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, fd)) break;
		node->year = atoi(bufor);

		head = push_student(head, node);
	}

	fclose(fd);
	printf("Wczytano listę z pliku tekstowego\n");
	return head;
}


Student *pop_student_head(Student **head) {
	if (!head)
		error(5, "ptr to ptr to head is null");

	if (!*head)
		return NULL;

	Student *s = *head;
	*head = (*head)->next;
	s->next = NULL;
	return s;
}


void free_student(Student *s) {
	free(s->name);
	free(s->surname);
	free(s);
}


void free_list(Student *head) {
	while (head)
		free_student(pop_student(&head));
}


int main(){
	Student *head = NULL;

	while (1) {
		print_menu(head);
		Menu m = get_integer("Podaj nr operacji", 0, get_menu_size(head) - 1);
		printf("\n");

		switch (m) {
			case PUSH:
				head = push_student(head, get_student());
				break;

			case POP:
				Student *to_remove = pop_student(&head);
				printf("Usunięto:\n");
				display_student(to_remove);
				free_student(to_remove);
				break;

			case FIND_BY_SURNAME:
				char *pattern = get_string("Enter surname pattern", MAX_BUFFOR);
				Student *found = find_student_by_surname(head, pattern);
				free(pattern);

				if (found) {
					printf("\nZnaleziono:\n");
					display_student(found);
				} else {
					printf("\nNieznaleziono\n");
				}
				break;

			case DISPLAY_LIST:
				display_list(head);
				break;

			case DISPLAY_LENGTH:
				display_list_length(head);
				break;

			case DROP_LIST:
				free_list(head);
				head = NULL;
				break;

			case SAVE_BIN_FILE:
				printf("todo");
				break;

			case READ_BIN_FILE:
				printf("todo");
				break;

			case READ_TEXT_FILE:
				head = read_list();
				break;

			default:
				return 0;
		}
	}
}