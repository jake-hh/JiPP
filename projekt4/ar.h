#ifndef AR_H_
#define AR_H_

#define TEXT_DATA_FILE_NAME "dane.txt"
#define BINARY_DATA_FILE_NAME "dane.dat"

#define MAX_BUFFOR 256
#define INITIAL_ARRAY_CAP 16



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

#endif