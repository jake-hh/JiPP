#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define DATA_FILE_NAME "dane.txt"

#define MAX_BUFFOR 256

typedef struct {
	char *name;
	char *surname;
	int year;
} Student;

typedef struct {
	Student **values;
	int capacity;
	int length;
} Student_list;

extern void error(int nr, const char *str);
extern char *copy_word(char *buf);
extern char *get_string(char *msg, int cap);
extern int get_integer(char *msg, int min, int max);


void print_menu(int length) {
	printf("\n[Menu]\n"
			"0 - Quit\n"
			"1 - Add student\n"
			"2 - Remove student\n"
			"3 - Find student by surname\n"
			"4 - Display list\n"
			"5 - Count students in list\n"
			"6 - Drop students list\n"
			"7 - Save to binary file\n");

	if (!length)
		printf("8 - Load from binary file\n"
				"9 - Load from text file\n");

	printf("\n");
}


int get_menu_size(int length) {
	return length ? NO_READ_MENU_SIZE : MENU_SIZE;
}


Student *get_student() {
	printf("\nDodawanie studenta\n");
	Student *s = (Student*)malloc(sizeof(Student));
	if (!s)
		error(4, "malloc student");

	s->name = get_string("Enter name", MAX_BUFFOR);
	s->surname = get_string("Enter surname", MAX_BUFFOR);
	s->year = get_integer("Enter year", 2000, 2100);
	return s;
}


Student *find_student_by_surname(Student_list list, char *surname) {
	// !strcmp(list.values[i]->surname, surname)
	for (int i = 0; i < list.length; i++)
		if (strstr(list.values[i]->surname, surname))
			return list.values[i];

	return NULL;
}


void display_list_length(int length) {
	printf("dlugosc listy = %d\n\n", length);
}


void display_student(Student *s) {
	if (s)
		printf("  %-10s| %-10s| %4d\n", s->name, s->surname, s->year);
	else
		printf("  NULL\n");
}


void display_list(Student_list list) {
	if (!list.length) {
		printf("Lista pusta\n");
		return;
	}
	else {
		printf("\n[Lista studentów]\n");
	}

	for (int i = 0; i < list.length; i++) {
		printf("%i:", i+1);
		display_student(list.values[i]);
	}
	display_list_length(list.length);
}


// --- wsadź element na końcu ---
void push_student(Student_list *list, Student *new_s) {
	if (!new_s)
		error(5, "pusty student");

	if (list->length >= list->capacity) {
		list->capacity *= 2;
		Student **tmp = (Student**) realloc(list->values, list->capacity * sizeof(Student*));
		if (!tmp)
			error(4, "realloc lista studentów");
		list->values = tmp;
	}

	list->values[list->length] = new_s;
	list->length++;
}


// --- usuń ostatni element ---
Student *pop_student(Student_list *list) {
	if (!list->length)
		return NULL;

	list->length--;
	return list->values[list->length];
}

void read_list(Student_list *list) {
	FILE *fd = fopen(DATA_FILE_NAME, "r");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku z danymi do odczytu!");

	char bufor[MAX_BUFFOR];

	while (fgets(bufor, MAX_BUFFOR, fd)) {

		Student *s = (Student*)malloc(sizeof(Student));
		if (!s)
			error(4, "malloc student");

		s->name = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, fd)) break;
		s->surname = copy_word(bufor);

		if(!fgets(bufor, MAX_BUFFOR, fd)) break;
		s->year = atoi(bufor);

		push_student(list, s);
	}

	fclose(fd);
	printf("Wczytano tablicę z pliku tekstowego\n");
}


void free_student(Student *s) {
	free(s->name);
	free(s->surname);
	free(s);
}


void free_list(Student_list *list) {
	int length = list->length;

	for (int i = 0; i < length; i++)
		free_student(pop_student(list));
}


int main() {
	const int INITIAL_CAP = 16;

	Student_list list;
	list.values = (Student**) malloc(INITIAL_CAP * sizeof(Student*));
	list.capacity = INITIAL_CAP;
	list.length = 0;

	if (!list.values)
		error(4, "malloc lista studentów");

	while (1) {
		print_menu(list.length);
		Menu m = get_integer("Podaj nr operacji", 0, get_menu_size(list.length) - 1);
		printf("\n");

		switch (m) {
			case PUSH:
				push_student(&list, get_student());
				break;

			case POP:
				Student *to_remove = pop_student(&list);
				printf("Usunięto:\n");
				display_student(to_remove);
				free_student(to_remove);
				break;

			case FIND_BY_SURNAME:
				char *pattern = get_string("Enter surname pattern", MAX_BUFFOR);
				Student *found = find_student_by_surname(list, pattern);
				free(pattern);

				if (found) {
					printf("\nZnaleziono:\n");
					display_student(found);
				} else {
					printf("\nNieznaleziono\n");
				}
				break;

			case DISPLAY_LIST:
				display_list(list);
				break;

			case DISPLAY_LENGTH:
				display_list_length(list.length);
				break;

			case DROP_LIST:
				free_list(&list);
				display_list_length(list.length);
				break;

			case SAVE_BIN_FILE:
				printf("todo");
				break;

			case READ_BIN_FILE:
				printf("todo");
				break;

			case READ_TEXT_FILE:
				read_list(&list);
				break;

			default:
				free_list(&list);
				return 0;
		}
	}
}