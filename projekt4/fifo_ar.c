#include <stdlib.h>
#include "ar.h"

extern void error(int nr, const char *str);
extern int run();
extern void resize_list(Student_list *list, int new_capacity);


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


int main() {
	return run();
}