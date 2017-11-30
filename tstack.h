/**
 * @Name IFJ17 Zasobnik
 * @author Tomas Lapsansky (xlapsa00)
 * @file tstack.h
 * @date 29.11.2017
 */

#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STACK 20

#include "symtable.h"

typedef struct {
	tHTable *table[MAX_STACK];
	int top;
} tStack;

int stackInit(tStack *s);
bool stackEmpty(tStack *s);
int stackPush(tStack *s, tHTable* ptrht);
tHTable* stackPop(tStack *s);

#endif
