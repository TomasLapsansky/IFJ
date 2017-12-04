#ifndef SCANNER
#define SCANNER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>

#include "structs.h"

#define INC_SIZE 8

enum Token_Name{
	ID = 10,
	INT_NUM,
	DOUBLE_NUM,
	STR,
	BL,
    PRINT_VAR,

	PLUS = 20,
	MINUS,
	TIMES,
	DIVISION,
	DIVISION_INT,

	GREATER = 30,
	LESSER,
	GREATEREQUAL,
	LESSEREQUAL,
	EQUAL,
	NOTEQUAL,

	LEFTPAREN = 40,
	RIGHTPAREN,

	COMMA = 50,
	SEMICOLON,
	INVALIDCHAR,

	EOF_ = 60,
	EOL_,
	P_EOL,
	undef_EOF,

	AS = 70,
	ASC,
	DECLARE,
	DIM,
	DO,
	DOUBLE,
	ELSE,
	END,
	CHR,
	FUNCTION,
	IF = 80,
	INPUT,
	INTEGER,
	LENGTH,
	LOOP,
	PRINT,
	RETURN,
	SCOPE,
	STRING,
	SUBSTR,
	THEN = 90,
	WHILE,
	AND,
	BOOLEAN_,
	CONTINUE,
	ELSEIF,
	EXIT,
	FALSE_,
	FOR,
	NEXT,
	NOT = 100,
	OR,
	SHARED,
	STATIC,
	TRUE_,
};

int Init_Token(TOKEN *t);
int Add_Char(TOKEN *t, char c);
void Clear_Token(TOKEN *t);
int KeywordCheck(char *string);
int Get_Token(TOKEN *t);
#endif
