/**
 * @Name IFJ17 Zasobnik
 * @author Tomas Lapsansky (xlapsa00)
 * @file tstack.c
 * @date 29.11.2017
 */

#include "tstack.h"

int stackInit(tStack *s) {
	
	if(s == NULL) {
		printf("stack alloc error\n");
		return ALLOC_ERROR;
	}
	
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
	
	s->table[s->top+1] = ptrht;
	
    printf("\n\n\n\n\nSTACK\nptrht = %p pushed\ninc top = %d\n\n\n\n\n", (void*)ptrht, s->top);
    
    s->top++;
	return OK;
}

tHTable* stackPop(tStack *s) {
	
    if(stackEmpty(s)) {
        //printf("STACKEMPTY!!!!!");
		return NULL;
    }
	
	s->top--;
    
    printf("\n\n\n\n\nSTACK\nptrht = %p poped\ntop = %d\n\n\n\n\n", (void*)s->table[s->top + 1], s->top);
    
	return s->table[s->top + 1];
}
