#include "scanner.h"
#include "parser.h"
#include "ts.h"
#include "tstack.h"
#include "structs.h"

FILE* f;
TOKEN token;
int error;		//error code
int line;		//line number

tStack s;
tHTable *ptrht;

int main(void) {
	Init_Token(&token);
	stackInit(&s);
	
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	htInit(&ptrht);
	
	f = fopen("code.txt","r");
	if (f == NULL){
		printf("Opening file code - ERROR \n");
		return 1;
	}
	
	int finish = parser();
	
	if(finish == OK) {
		printf("CODE1: OK\n");
	} else if(finish == SYN_A_ERROR) {
		printf("CODE1: SYN_A_ERROR line = %d token = %d\n", line, token.name);
	} else if(finish == LEX_A_ERROR) {
		printf("CODE1: LEX_A_ERROR line = %d token = %d\n", line, token.name);
	} else if(finish == SEM_ERROR) {
		printf("CODE1: SEM_ERROR line = %d token = %d\n", line, token.name);
	} else if(finish == SEM_TYPE_ERROR) {
		printf("CODE1: SEM_TYPE_ERROR line = %d token = %d\n", line, token.name);
	}
	
	fclose(f);
	Clear_Token(&token);
	DELETE_TS(&ptrht);
	return 0;
}

