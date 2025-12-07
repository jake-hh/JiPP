#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h>

#define MAX_CHARS 1024
#define MAX_LINES 200

#define MODE_ENCODE 'e'
#define MODE_DECODE 'd'
#define CMD_ENCODE "--encode"
#define CMD_DECODE "--decode"

const char litery[] = {'a',165,'b','c',134,'d','e',169,'f','g','h','i','j','k','l',136,
'm','n',228,'o',162,'p','q','r','s',152,'t','u','v','w','x','y','z',190,171,
'A',164,'B','C',143,'D','E',168,'F','G','H','I','J','K','L',157,'M','N',
227,'O',224,'P','Q','R','S',151,'T','U','V','W','X','Y','Z',189,141,' ',
'.',',','?',':','-','0','1','2','3','4','5','6','7','8','9','!','\0'};

const char *mors[] = { ".-",".-.-","-...","-.-.","-.-..","-..",".","..-..","..-.","--.",
"....","..",".---","-.-",".-..",".-..-","--","-.","--.--","---","---.",
".--.","--.-",".-.","...","...-...","-","..-","...-",".--","-..-","-.--",
"--..","--..-","--..-.",".-",".-.-","-...","-.-.","-.-..","-..",".","..-..",
"..-.","--.","....","..",".---","-.-",".-..",".-..-","--","-.","--.--",
"---","---.",".--.","--.-",".-.","...","...-...","-","..-","...-",".--",
"-..-","-.--","--..","--..-","--..-.","/",".-.-.-","--..--","..--..","---..",
"-....-","-----",".----","..---","...--","....-",".....","-....","--...","---..","----.","!",0};

char **read_file(const char *file_name, int *lines_count);
void print_lines(char **d, int lines_count);
const char *encode_char(char dec);
char decode_char(char *enc);
void encode(char **d, char* fout);
void decode(char **d, char* fout);
void print_help();
char get_mode(char *cmd);


int main(int argc, char **argv) {
	// setlocale(LC_ALL, "Polish_Poland.1250");
	printf("Program do konwertowania na kod morsa\n");

	if (argc != 4) {
		printf("Zła liczba argumentów\n");
		print_help();
		exit(1);
	}

	char mode = get_mode(argv[1]);

	/* Tekst w pamieci, tablica d - wskazniki do linii tekstu */
	int lines_count = 0;
	char **d = read_file(argv[2], &lines_count);

	printf("Ilosc linii: %d\n", lines_count);

	print_lines(d, lines_count);

	printf("Encoding\n");
	if (mode == MODE_ENCODE)
		encode(d, argv[3]);
	else
		decode(d, argv[3]);

}


char **read_file(const char *file_name, int *lines_count) {
	FILE *fd;
	char **d, bufor[MAX_CHARS];
	int len, i, l;

	if (!(d = (char**)malloc(MAX_LINES))) {
			printf("Brak pamieci\n");
			exit(3);
	}

	if (!(fd = fopen(file_name, "r"))) {
		printf("Blad otwarcia zbioru\n");
		exit(2);
	}

	i = 0;
	l = 0;
	while (i < MAX_LINES && fgets(bufor, MAX_CHARS, fd)) {

		len = strlen(bufor);
		bufor[len - 1] = '\0';

		if (!(d[i] = (char*)malloc((unsigned)len))) {
			printf("Brak pamieci\n");
			exit(4);
		}

		strcpy(d[i], bufor);
		i++;
	}

	d[i] = (char *)0; //znacznik końca tablicy wskaźników
	*lines_count = i;
	fclose(fd);

	return d;
}


void print_lines(char **d, int lines_count) {
	printf("\n[zawartość tablicy]\n");

	for (int i = 0; i < lines_count; i++)
		printf("%d: %s\n", i + 1, d[i]);

	printf("\n");
}


char get_mode(char *cmd) {
	if (!strcmp(cmd, CMD_ENCODE))
		return MODE_ENCODE;
	if (!strcmp(cmd, CMD_DECODE))
		return MODE_DECODE;

	printf("Zla komenda\n");
	print_help();
	exit(1);
}


void print_help() {
	printf("\nUsage: morse_code [cmd] [in_file] [out_file]\n");
	printf("cmd: %s | %s\n", CMD_ENCODE, CMD_DECODE);
}


const char *encode_char(char dec) {
	int i = 0;
	while (litery[i] && litery[i] != dec) i++;

	const char *enc;
	if (litery[i] == '\0')
		enc = "?";
	else
		enc = mors[i];

	return enc;
}


void encode(char **d, char* fout) {
	FILE *fd;

	if (!(fd = fopen(fout, "w"))) {
		printf("Blad otwarcia pliku wyjsciowego\n");
		exit(7);
	}

	while (*d != (char *)0) {
		char *c = *d;

		while (*c) {
			const char *enc = encode_char(*c);
			fwrite(enc, sizeof(char), strlen(enc), fd);
			fputc(' ', fd);
			c++;
		}

		fputc('\n', fd);
		d++;
	}

	fclose(fd);
}


char decode_char(char *enc) {
	int i = 0;
	while(mors[i] && strcmp(enc, mors[i])) i++;

	char dec;
	if (mors[i])
		dec = litery[i];
	else
		dec = '?';

	return dec;
}


void decode(char **d, char* fout) {
	FILE *fd;

	if (!(fd = fopen(fout, "w"))) {
		printf("Blad otwarcia pliku wyjsciowego\n");
		exit(7);
	}

	while (*d != (char *)0) {
		char *enc = strtok(*d, " ");

		while (enc) {
			char dec = decode_char(enc);
			fputc(dec, fd);
			enc = strtok(NULL, " ");
		}

		fputc('\n', fd);
		d++;
	}

	fclose(fd);
}