/**
 * @Name IFJ17 Precedencni syntatkicka analyza - seznam funkce
 * @author Marek Kalabza (xkalab09)
 * @file psalist.c
 * @date 5.11.2017
 */
#include "psalist.h"
#include "structs.h"

#include <stdlib.h>

// prevede data na int
int give_me_int(char *data){
	int i = atoi(data);
	return i;
}

// prevede data na int
double give_me_double(char *data){
	double d = strtod(data,NULL);
	return d;
}

// funkce na prevod na int
int double_to_int(double d){
	int i = (int) d;
	return i;
}

// funkce na prevod na double
double int_to_double(int i){
	double d = (double) i;
	return d;
}

// inicializace seznamu pro PSA
psa_list *psa_list_init(){
	psa_list *list;

	if((list = malloc(sizeof(psa_list))) == NULL){
		return NULL;
	}

	list->top = NULL;
	return list;
}

// smazani seznamu pro PSA
void psa_list_delete(psa_list *list){
	while(list->top != NULL){
		psa_item *next = list->top->lptr;
		free(list->top);
		list->top = next;
	}
	free(list);
}

// vlozi item na top seznamu
int psa_list_push(psa_list *list, psa_item *item){
	if(item != NULL){
		if (list->top != NULL){
			list->top->rptr = item;
		}
		item->lptr = list->top;
		list->top = item;
	}
	else{
		return SYN_A_ERROR;
	}

	return OK;
}

// odebere top seznamu
void psa_list_pop(psa_list *list){
	if(list->top != NULL){
		psa_item *item = list->top;
		item->lptr->rptr = NULL;
		list->top = item->lptr;
		free(item);
	}
}

// vlozi item za nejaky dany TERM v seznamu, potrebny na vlozeni OP_EXP = <
int psa_list_push_after_item(psa_list *list,psa_item *item,psa_item *newitem){
	if(item != NULL){
		newitem->lptr = item;
		item->rptr->lptr = newitem;
		newitem->rptr = item->rptr;
	    item->rptr = newitem;
	    if(newitem->rptr == NULL){
	    	newitem = list->top;
	    }
	}
	else{
		return SYN_A_ERROR;
	}

	return OK;
}

// vrati item na topu seznamu
psa_item *psa_list_top(psa_list *list){
	return list->top;
}

// vytvoreni itemu psa
psa_item *psa_create_item(){
	psa_item *item = malloc(sizeof(psa_item));
	item->oper = OP_EXP;
	item->lptr = NULL;
	item->rptr = NULL;
	strcpy(item->name," ");
	return item;
}

// vyhleda TERM v seznamu
psa_item *psa_search_term(psa_list *list){
	psa_item *item = list->top;

	while((item->oper > 13)&&(item->oper != 16)){
		item = item->lptr;
	}
	//printf("FIRST TERM: %d\n",item->oper);
	return item;
}

// vypise seznam
void psa_list_show(psa_list *list){
	psa_item *item = list->top;
	if(list->top == NULL){
		return;
	}
	while(item->lptr != NULL){
		item = item->lptr;
	}
	while(item->rptr != NULL){
		printf("%d|",item->oper );
		item = item->rptr;
	}
	printf("%d|\n",item->oper );
}

