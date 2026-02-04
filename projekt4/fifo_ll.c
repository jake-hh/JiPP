#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "ll.h"

extern void error(int nr, const char *str);
extern int run();


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


int main(){
	return run();
}