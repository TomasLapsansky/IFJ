#include "string.h"
#include <stdio.h>
#include <string.h>

void toString(TOKEN token) {
	
	for(unsigned long i = 0; i < strlen(token.data); i++) {
		if((token.data[i] >= 48 && token.data[i] <= 57) || (token.data[i] >= 65 && token.data[i] <= 90) || (token.data[i] >= 97 && token.data[i] <= 122))
			printf("%c", token.data[i]);
		else {
				if(token.data[i] < 10)
					printf("\\00%d", token.data[i]);
				else if(token.data[i] < 100)
					printf("\\0%d", token.data[i]);
				else
					printf("\\%d", token.data[i]);
		}
	}
}
