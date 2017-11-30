#include "scanner.h"
#include "parser.h"
#include "ts.h"
#include "tstack.h"

TOKEN token;
int error;		//error code
int line;		//line number
tHTable* ptrht;	//HASH table
tStack *s;
int loadedc = 0;

int main(void) {
	
	ptrht = (tHTable*)malloc(sizeof(tHTable));
	
	Init_Token(&token);
	htInit(ptrht);
	stackInit(s);
	
	int final = parser();
	
	htPrintTable(ptrht);
	
	if(final == OK) {
		DELETE_TS(ptrht);
		Clear_Token(&token);
		return 0;
	} else {
		printf("%d on line %d\ntoken.name = %d\ntoken.data = %s\n", final, line, token.name, token.data);
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

