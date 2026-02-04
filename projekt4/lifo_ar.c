#include <stdlib.h>
#include "ar.h"

extern void error(int nr, const char *str);
extern int run();
extern void resize_list(Student_list *list, int new_capacity);


// --- usuń ostatni element ---
Student *pop_student(Student_list *list) {
	if (!list->length)
		return NULL;

	if (list->length <= list->capacity / 3 - 8)
		resize_list(list, list->capacity / 2);

	list->length--;
	return list->values[list->length];
}


int main() {
	return run();
}