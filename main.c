#include "scanner.h"
#include "parser.h"
#include "ts.h"

TOKEN token;
int error;		//error code
int line;		//line number
tHTable* ptrht;	//HASH table

int main(void) {
	
	ptrht = (tHTable*)malloc(sizeof(tHTable));
	
	Init_Token(&token);
	htInit(ptrht);
	
	int final = parser();
	
	DELETE_TS(ptrht);
	Clear_Token(&token);
	
	if(final == OK) {
		return 0;
	} else {
		printf("%d on line %d\ntoken = %d\n", final, line, token.name);
		return final;
	}
}

