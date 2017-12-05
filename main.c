/**
 * @Name IFJ17 Main pre prekladac
 * @author Tomas Lapsansky (xlapsa00)
 * @file main.c
 * @date 5.12.2017
 */

#include "scanner.h"
#include "parser.h"
#include "symtable.h"
#include "tstack.h"

TOKEN token;
int error;		//error code
int line;		//line number
tHTable* ptrht;	//HASH table
tHTable* global_ptrht;
tStack *s;
int loadedc = 0;

int main(void) {
	
	ptrht = (tHTable*)malloc(sizeof(tHTable));
    global_ptrht = ptrht;
	s = (tStack*)malloc(sizeof(tStack));
	if(ptrht == NULL)
        return ALLOC_ERROR;
	if(s == NULL)
		return ALLOC_ERROR;
	Init_Token(&token);
	htInit(ptrht);
	stackInit(s);
    
	int final = parser();
    
	if(final == OK) {
		DELETE_TS(ptrht);
		Clear_Token(&token);
		return 0;
	} else {
        //pomocne vypisi
        //printf("ERROR: %d on line %d\n", final, line);
        //printf("token.name = %d\ntoken.data = %s\n", token.name, token.data);
		DELETE_TS(ptrht);
		Clear_Token(&token);
		return final;
	}

/* *********** KONTROLA LEXIKALNI ANALYZY **************** */
/*
int pom;
while((pom = Get_Token(&token)) != EOF){
		if(pom == LEX_A_ERROR){
			printf("LEX_A_ERROR\n");
			break;
			return 1;
		}
		else if(pom == ALLOC_ERROR){
			printf("ALLOC_ERROR\n");
			break;
			return 1;
		}
		else{
			printf("[data: %s | name: %d]\n\n",token.data, token.name);
		}
		Clear_Token(&token);
	}
*/
	//DELETE_TS(ptrht);
	//Clear_Token(&token);
}

