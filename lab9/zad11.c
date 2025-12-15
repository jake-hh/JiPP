#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STUDENTS 10
#define BUF_LEN 128

typedef struct student {
	char* imie;
	char* nazwisko;
	int rok;
	char* adres;
	double stypendium;
} STUDENT;


STUDENT **read_file(char *filename) {
	FILE *fd = fopen(filename, "r");
	if (!fd) {
		printf("Error opening file %s", filename);
		exit(2);
	}

	// Initialize variables <<<<<<<<<<<
	int i, len, max_s, max_s_pos;

	char *buf = (char*)malloc(sizeof(char) * BUF_LEN);
	STUDENT **t = (STUDENT**)malloc(sizeof(STUDENT*) * MAX_STUDENTS);

	for (i = 0; i < MAX_STUDENTS && fgets(buf, BUF_LEN, fd) != (char*)NULL; i++) {
		STUDENT tmp;

		len = (unsigned)strlen(buf);
		buf[len - 1] = '\0';
		tmp.imie = (char*)malloc(len);
		strcpy(tmp.imie, buf);
		
		if (fgets(buf, BUF_LEN, fd) == (char*)NULL) break;
		len = (unsigned)strlen(buf);
		buf[len - 1] = '\0';
		tmp.nazwisko = (char*)malloc(len);
		strcpy(tmp.nazwisko, buf);

		if (fgets(buf, BUF_LEN, fd) == (char*)NULL) break;
		tmp.rok = atoi(buf);

		if (fgets(buf, BUF_LEN, fd) == (char*)NULL) break;
		len = (unsigned)strlen(buf);
		buf[len - 1] = '\0';
		tmp.adres = (char*)malloc(len);
		strcpy(tmp.adres, buf);

		if (fgets(buf, BUF_LEN, fd) == (char*)NULL) break;
		tmp.stypendium = atoi(buf);

		if(i == 0 || tmp.stypendium > max_s) {
			max_s = tmp.stypendium;
			max_s_pos = i;
		}

		t[i] = &tmp;
	}

	return 0;
}


void bubble_sort_desc_studenty(STUDENT *t[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (t[j]->stypendium < t[j + 1]->stypendium) {
                STUDENT *tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
}

void bubble_sort_desc(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] < a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Podaj plik wejściowy");
		return 1;
	}
	// STUDENT **studenty = read_file(argv[1]);

	int a[] = {5, 1, 4, 2, 8};
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\nn: %d\n", n);
	bubble_sort_desc(a, n);
	for (int i = 0; i < n; i++) printf("%d ", a[i]);
	printf("\n");

	return 0;
}
