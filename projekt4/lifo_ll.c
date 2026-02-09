// clear; gcc -g -O0 lifo_ll.c ll.c util_?.c -o lifo_ll
// clear; gcc lifo_ll.c ll.c util_?.c -o lifo_ll

#include <stdlib.h>
#include "ll.h"

extern void error(int nr, const char *str);
extern int run();


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


int main(){
	return run();
}