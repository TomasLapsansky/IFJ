#include "../scanner.h"
#include "../parser.h"


FILE* f;
TOKEN token;
int error;		//error code
int line;		//line number

int main(void) {
	Init_Token(&token);
	
	f = fopen("../code.txt","r");
	if (f == NULL){
		printf("Opening file - ERROR \n");
		return 1;
	}
	
	int finish = parser();
	
	if(finish == OK) {
		printf("OK line = %d token = %d\n", line, token.name);
	} else if(finish == E_OK) {
		printf("E_OK line = %d token = %d\n", line, token.name);
	} else if(finish == SYN_A_ERROR) {
		printf("SYN_A_ERROR line = %d token = %d\n", line, token.name);
	} else if(finish == LEX_A_ERROR) {
		printf("LEX_A_ERROR line = %d token = %d\n", line, token.name);
	}
	
	Clear_Token(&token);
	return 0;
}
