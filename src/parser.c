#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	int currentStatus = STATUS_INITIAL;
	int offset = 0;
	char currentChar = *(text + offset);
	int finish = 0;
	
	TRANSITION currentTransition;
	
	memset(token, 0, sizeof(TOKEN));
	
	while(!finish) {
		currentChar = *(text + offset);
        //printf("[%i][%c] -> ", currentStatus, currentChar);
		currentTransition = transTable->transitions[currentStatus][currentChar];
		
		if(currentTransition.function != NULL)
			currentTransition.function(&finish, token);
			
		currentStatus = currentTransition.nextStatus;
        //printf("%i\n", currentStatus);
		offset++;
	}
	
	return token;
}
