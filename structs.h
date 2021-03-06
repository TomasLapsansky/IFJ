/**
 * @Name IFJ17 Struktury
 * @author Marek Kalabza (xkalab09)
 * @file structs.c
 * @date 14.10.2017
 */

#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdbool.h>

typedef struct{
        char *data;
        int alloc_size;
        int size;
        int name;
}TOKEN;

enum Errors{
	E_OK = -1,
	OK = 7,
	LEX_A_ERROR = 1,
	SYN_A_ERROR = 2,
	SEM_ERROR = 3,
	SEM_TYPE_ERROR = 4,
	OTHER_SEM_ERROR = 6,
	ALLOC_ERROR = 99,
};

enum ID_values{
	F_ID = 1,
	DIM_ID,
	UNEXIST,
	NON_ID,
};

#endif
