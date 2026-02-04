#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define TEXT_DATA_FILE_NAME "dane.txt"
#define BINARY_DATA_FILE_NAME "dane.dat"

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


int get_list_length(Student *head) {
	int len = 0;

	while (head) {
		head = head->next;
		len++;
	}

	return len;
}


void display_list_length(Student *head) {
	printf("dlugosc listy = %d\n\n", get_list_length(head));
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


// --- usuń pierwszy element ---
Student *pop_student(Student **head) {
	if (!head)
		error(5, "ptr to ptr to head is null");

	if (!*head)
		return NULL;

	Student *s = *head;
	*head = (*head)->next;
	s->next = NULL;
	return s;
}


Student *read_list_text(const char *filename) {
	// open file for reading
	FILE *fd = fopen(filename, "r");
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


void write_list_binary(Student *head, const char *filename) {
	// open file for writing
	FILE *fd = fopen(filename , "wb");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku binarnego do zapisu");

	int length = get_list_length(head);

	// write list size to file
	if (fwrite(&length, sizeof(length), 1, fd) != 1)
		error(7, "Could not write number of students to file");

	for (int i = length - 1; i >= 0; i--) {

		Student *node = head;
		for (int j = 0; j < i; j++)
			node = node->next;

		int name_len = strlen(node->name) + 1;

		// write name length to file
		if (fwrite(&name_len, sizeof(name_len), 1, fd) != 1)
			error(7, "Could not write student name length to file");

		// write student name to file
		if (fwrite(node->name, sizeof(char), name_len, fd) != name_len)
			error(7, "Could not write student name to file");

		int surname_len = strlen(node->surname) + 1;

		// write surname length to file
		if (fwrite(&surname_len, sizeof(surname_len), 1, fd) != 1)
			error(7, "Could not write student surname length to file");

		// write student surname to file
		if (fwrite(node->surname, sizeof(char), surname_len, fd) != surname_len)
			error(7, "Could not write student surname to file");

		// write year length to file
		if (fwrite(&node->year, sizeof(node->year), 1, fd) != 1)
			error(7, "Could not write student year to file");
	}

	fclose(fd);
	printf("Saved to binary file successfully\n");
}


void read_list_binary(Student **head, const char *filename) {
	// open file for reading
	FILE *fd = fopen(filename , "rb");
	if (!fd)
		error(2, "Nie mogę otworzyć pliku binarnego do odczytu");

	// read list size from file
	int length;
	if (fread(&length, sizeof(length), 1, fd) != 1)
		error(3, "Could not read number of students from file");

	for (int i = 0; i < length; i++) {

		Student *node = (Student*)malloc(sizeof(Student));
		if (!node)
			error(4, "malloc student");

		// read name length from file
		int name_len;
		if (fread(&name_len, sizeof(name_len), 1, fd) != 1)
			error(3, "Could not read student name length from file");

		node->name = (char*)malloc(name_len);
		if (!node->name)
			error(4, "malloc read_list_binary");

		// read student name from file
		if (fread(node->name, sizeof(char), name_len, fd) != name_len)
			error(3, "Could not read student name from file");

		// read surname length from file
		int surname_len;
		if (fread(&surname_len, sizeof(surname_len), 1, fd) != 1)
			error(3, "Could not read student surname length from file");

		node->surname = (char*)malloc(surname_len);
		if (!node->surname)
			error(4, "malloc read_list_binary");

		// read student surname from file
		if (fread(node->surname, sizeof(char), surname_len, fd) != surname_len)
			error(3, "Could not read student surname from file");

		// read year length from file
		if (fread(&node->year, sizeof(node->year), 1, fd) != 1)
			error(3, "Could not read student year from file");

		*head = push_student(*head, node);
	}

	fclose(fd);
	printf("Read from binary file successfully\n");
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
		print_menu();
		Menu m = get_integer("Podaj nr operacji", 0, MENU_SIZE - 1);
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
				write_list_binary(head, BINARY_DATA_FILE_NAME);
				break;

			case READ_BIN_FILE:
				read_list_binary(&head, BINARY_DATA_FILE_NAME);
				break;

			case READ_TEXT_FILE:
				head = read_list_text(TEXT_DATA_FILE_NAME);
				break;

			default:
				return 0;
		}
	}
}