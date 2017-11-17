#include "../scanner.h"
#include "../parser.h"

FILE *f;
TOKEN token;

int main(void) {
	Init_Token(&token);
	
	f = fopen("../code.txt","r");
	if (f == NULL){
		printf("Opening file - ERROR \n");
		return 1;
	}
	
	int finish = parser();
	
	printf("%d\n", finish);
	
	Clear_Token(&token);
	return 0;
}
