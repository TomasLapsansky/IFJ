#include "../scanner.h"
#include "../parser.h"

int main(void) {
	FILE *f;
	
	f = fopen("../code.txt","r");
	if (f == NULL){
		printf("Opening file - ERROR \n");
		return 1;
	}
	
	int finish = parser();
	
	printf("%d\n", finish);
	
	return 0;
}
