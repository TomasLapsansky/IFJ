#include "scanner.h"

int main(){
	FILE *f;
	int pom = undef_EOF;
	TOKEN t;
	Init_Token(&t);

	f = fopen("code.txt","r");
	if (f == NULL){
		printf("Opening file - ERROR \n");
        return 1;
	}

	while((pom = Get_Token(f,&t)) != undef_EOF){
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
			printf("[data: %s | name: %d]\n\n",t.data, t.name);
		}
		Clear_Token(&t);
	}

	fclose(f);

	return 0;
}
