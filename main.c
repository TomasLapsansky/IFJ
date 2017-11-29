#include "scanner.h"
#include "parser.h"
#include "ts.h"
#include "tstack.h"

TOKEN token;
int error;		//error code
int line;		//line number
tHTable* ptrht;	//HASH table
tStack *s;

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
	
	//DELETE_TS(ptrht);
	//Clear_Token(&token);
}

