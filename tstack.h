#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STACK 20

#include "ts.h"

typedef struct {
	tHTable *table[MAX_STACK];
	int top;
} tStack;

int stackInit(tStack *s);
bool stackEmpty(tStack *s);
int stackPush(tStack *s, tHTable* ptrht);
tHTable* stackPop(tStack *s);

#endif
