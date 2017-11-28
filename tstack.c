/**
 * @Name IFJ17 Zasobnik
 * @author Tomas Lapsansky (xlapsa00)
 * @file tstack.c
 * @date 29.11.2017
 */

#include "tstack.h"

int stackInit(tStack *s) {
	
	if(s == NULL)
		return ALLOC_ERROR;
	
	s->top = -1;
	
	return OK;
}

bool stackEmpty(tStack *s) {
	
	if(s->top == -1)
		return true;
	else
		return false;
}

int stackPush(tStack *s, tHTable* ptrht) {
	
	if(s->top == (MAX_STACK - 1))
		return ALLOC_ERROR;
	
	s->table[s->top] = ptrht;
	
	return OK;
}

tHTable* stackPop(tStack *s) {
	
	if(!stackEmpty(s))
		return NULL;
	
	s->top--;
	
	return s->table[s->top + 1];
}
