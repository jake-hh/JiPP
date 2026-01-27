#ifndef MENU_H_
#define MENU_H_

#define MENU_SIZE 10
#define NO_READ_MENU_SIZE 10

typedef enum {
	// READ_LIST,
	/* 0 */ QUIT,
	/* 1 */ PUSH,
	/* 2 */ POP,
	/* 3 */ FIND_BY_SURNAME,
	/* 4 */ DISPLAY_LIST,
	/* 5 */ DISPLAY_LENGTH,
	/* 6 */ DROP_LIST,
	/* 7 */ SAVE_BIN_FILE,
	/* 8 */ READ_BIN_FILE,
	/* 9 */ READ_TEXT_FILE,
} Menu;

#endif