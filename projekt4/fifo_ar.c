#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define TEXT_DATA_FILE_NAME "dane.txt"
#define BINARY_DATA_FILE_NAME "dane.dat"

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


void print_menu() {
	printf("\n[Menu]\n"
			"0 - Quit\n"
			"1 - Add student\n"
			"2 - Remove student\n"
			"3 - Find student by surname\n"
			"4 - Display list\n"
			"5 - Count students in list\n"
			"6 - Drop students list\n"
			"7 - Save to binary file\n"
			"8 - Load from binary file\n"
			"9 - Load from text file\n\n");
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


void resize_list(Student_list *list, int new_capacity) {
	Student **tmp = (Student**) realloc(list->values, new_capacity * sizeof(Student*));
	if (!tmp)
		error(4, "realloc lista studentów");
	list->values = tmp;
	list->capacity = new_capacity;
}


// --- wsadź element na końcu ---
void push_student(Student_list *list, Student *new_s) {
	if (!new_s)
		error(5, "pusty student");

	if (list->length >= list->capacity)
		resize_list(list, list->capacity * 2);

	list->values[list->length] = new_s;
	list->length++;
}


// --- usuń pierwszy element ---
Student *pop_student(Student_list *list) {
	if (!list->length)
		return NULL;

	if (list->length <= list->capacity / 3 - 8)
		resize_list(list, list->capacity / 2);

	Student *pop = list->values[0];
	list->length--;

	for (int i = 0; i < list->length; i++)
		list->values[i] = list->values[i + 1];

	return pop;
}


void read_list_text(Student_list *list, const char *filename) {
	FILE *fd = fopen(filename, "r");
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


void write_list_binary(Student_list list, const char *filename) {
	if (!list.length)
		return;

	// open file for writing
	FILE *fd = fopen(filename , "wb");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku binarnego do zapisu");

	// write list size to file
	if (fwrite(&list.length, sizeof(list.length), 1, fd) != 1)
		error(7, "Could not write number of students to file");

	for (int i = 0; i < list.length; i++) {

		int name_len = strlen(list.values[i]->name) + 1;

		// write name length to file
		if (fwrite(&name_len, sizeof(name_len), 1, fd) != 1)
			error(7, "Could not write student name length to file");

		// write student name to file
		if (fwrite(list.values[i]->name, sizeof(char), name_len, fd) != name_len)
			error(7, "Could not write student name to file");

		int surname_len = strlen(list.values[i]->surname) + 1;

		// write surname length to file
		if (fwrite(&surname_len, sizeof(surname_len), 1, fd) != 1)
			error(7, "Could not write student surname length to file");

		// write student surname to file
		if (fwrite(list.values[i]->surname, sizeof(char), surname_len, fd) != surname_len)
			error(7, "Could not write student surname to file");

		// write year length to file
		if (fwrite(&list.values[i]->year, sizeof(list.values[i]->year), 1, fd) != 1)
			error(7, "Could not write student year to file");
	}

	fclose(fd);
	printf("Saved to binary file successfully\n");
}


void read_list_binary(Student_list *list, const char *filename) {

	// open file for writing
	FILE *fd = fopen(filename , "rb");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku binarnego do odczytu");

	// read list size from file
	int length;
	if (fread(&length, sizeof(list->length), 1, fd) != 1)
		error(3, "Could not read number of students from file");

	resize_list(list, length + 8);

	for (int i = 0; i < length; i++) {

		Student *s = (Student*)malloc(sizeof(Student));
		if (!s)
			error(4, "malloc student");

		// read name length from file
		int name_len;
		if (fread(&name_len, sizeof(name_len), 1, fd) != 1)
			error(3, "Could not read student name length from file");

		s->name = (char*)malloc(name_len);
		if (!s->name)
			error(4, "malloc read_list_binary");

		// read student name from file
		if (fread(s->name, sizeof(char), name_len, fd) != name_len)
			error(3, "Could not read student name from file");

		// read surname length from file
		int surname_len;
		if (fread(&surname_len, sizeof(surname_len), 1, fd) != 1)
			error(3, "Could not read student surname length from file");

		s->surname = (char*)malloc(surname_len);
		if (!s->surname)
			error(4, "malloc read_list_binary");

		// read student surname from file
		if (fread(s->surname, sizeof(char), surname_len, fd) != surname_len)
			error(3, "Could not read student surname from file");

		// read year length from file
		if (fread(&s->year, sizeof(s->year), 1, fd) != 1)
			error(3, "Could not read student year from file");

		push_student(list, s);
	}

	fclose(fd);
	printf("Read from binary file successfully\n");
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
		print_menu();
		Menu m = get_integer("Podaj nr operacji", 0, MENU_SIZE - 1);
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
				write_list_binary(list, BINARY_DATA_FILE_NAME);
				break;

			case READ_BIN_FILE:
				read_list_binary(&list, BINARY_DATA_FILE_NAME);
				break;

			case READ_TEXT_FILE:
				read_list_text(&list, TEXT_DATA_FILE_NAME);
				break;

			default:
				free_list(&list);
				return 0;
		}
	}
}