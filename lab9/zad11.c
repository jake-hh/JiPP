#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STUDENTS 10
#define BUF_LEN 128 // zmieniajac wartosc zmien w fscanf-ach

typedef struct student {
	char* imie;
	char* nazwisko;
	int rok;
	char* adres;
	double stypendium;
} STUDENT;


void print_student(STUDENT *s) {
	printf("%s %s %d %s %g\n", s->imie, s->nazwisko, s->rok, s->adres, s->stypendium);
}


// save max_s_pos & max_s
STUDENT **read_file(char *filename, int *n) {
	FILE *fd = fopen(filename, "r");
	if (!fd) {
		printf("Error opening file %s\n", filename);
		exit(2);
	}

	int i, max_s_pos;
	double max_s;

	char *buf = (char*)malloc(sizeof(char) * BUF_LEN);
	STUDENT **t = (STUDENT**)malloc(sizeof(STUDENT*) * MAX_STUDENTS);

	for (i = 0; i < MAX_STUDENTS; i++) {
		STUDENT *s = (STUDENT*) malloc(sizeof(STUDENT));

		if (fscanf(fd, "%127s", buf) != 1) break;
		s->imie = (char*)malloc((unsigned)strlen(buf) + 1);
		strcpy(s->imie, buf);

		if (fscanf(fd, "%127s", buf) != 1) break;
		s->nazwisko = (char*)malloc((unsigned)strlen(buf) + 1);
		strcpy(s->nazwisko, buf);

		if (fscanf(fd, "%i", &s->rok) != 1) break;

		if (fscanf(fd, "%127s", buf) != 1) break;
		s->adres = (char*)malloc((unsigned)strlen(buf) + 1);
		strcpy(s->adres, buf);

		if (fscanf(fd, "%lf", &s->stypendium) != 1) break;

		if(i == 0 || s->stypendium > max_s) {
			max_s = s->stypendium;
			max_s_pos = i;
		}

		t[i] = s;
	}

	*n = i;
	// STUDENT **t = (STUDENT**)realloc(t, sizeof(STUDENT*) * n);
	return t;
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


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Podaj plik wejściowy\n");
		return 1;
	}

	// Wczytanie danych z pliku
	int n;
	STUDENT **studenty = read_file(argv[1], &n);

	printf("-- WCZYTANE STUDENTY --\n");
	for (int i = 0; i < n; i++) print_student(studenty[i]);
	printf("\n");

	// Posortowanie studentów wg stypendium
	bubble_sort_desc_studenty(studenty, n);

	printf("-- POSORTOWANE STUDENTY --\n");
	for (int i = 0; i < n; i++) print_student(studenty[i]);
	printf("\n");

	// Zwolnienie pamięci
	for (int i = 0; i < n; i++) {
		free(studenty[i]->imie);
		free(studenty[i]->nazwisko);
		free(studenty[i]->adres);
		free(studenty[i]);
	}
	free(studenty);
	studenty = NULL;

	return 0;
}
