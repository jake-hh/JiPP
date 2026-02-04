#ifndef LL_H_
#define LL_H_

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

#endif