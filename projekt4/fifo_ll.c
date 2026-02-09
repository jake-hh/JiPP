// clear; gcc -g -O0 fifo_ll.c ll.c util_?.c -o fifo_ll
// clear; gcc fifo_ll.c ll.c util_?.c -o fifo_ll

#include <stdlib.h>
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