#ifndef SCANNER
#define SCANNER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "structs.h"

extern FILE* f;

#define INC_SIZE 8

enum Token_Name{
	ID = 10,
	INT_NUM,
	DOUBLE_NUM,
	STR,

	PLUS,
	MINUS,
	TIMES,
	DIVISION,
	DIVISION_INT,

	GREATER,
	LESSER,
	GREATEREQUAL,
	LESSEREQUAL,
	EQUAL,
	NOTEQUAL,
	ASSIGN,

	LEFTPAREN,
	RIGHTPAREN,
	LEFTBRACE,
	RIGHTBRACE,

	DOT,
	COMMA,
	SEMICOLON,
	INVALIDCHAR,

	AS,
	ASC,
	DECLARE,
	DIM,
	DO,
	DOUBLE,
	ELSE,
	END,
	CHR,
	FUNCTION,
	IF,
	INPUT,
	INTEGER,
	LENGTH,
	LOOP,
	PRINT,
	RETURN,
	SCOPE,
	STRING,
	SUBSTR,
	THEN,
	WHILE,
	AND,
	BOOLEAN_,
	CONTINUE,
	ELSEIF,
	EXIT,
	FALSE_,
	FOR,
	NEXT,
	NOT,
	OR,
	SHARED,
	STATIC,
	TRUE_,
};

int Init_Token(TOKEN *t);
int Add_Char(TOKEN *t, char c);
void Clear_Token(TOKEN *t);
int KeywordCheck(char *string);
int Get_Token(FILE *f,TOKEN *t);
#endif
