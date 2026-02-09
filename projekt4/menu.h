#ifndef MENU_H_
#define MENU_H_

#define MENU_SIZE 10
#define FIELD_TYPE_MENU_SIZE 4

typedef enum {
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

typedef enum {
	/* 0 */ SKIP,
	/* 1 */ NAME,
	/* 2 */ SURNAME,
	/* 3 */ YEAR,
} FieldType;

#endif