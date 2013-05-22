#include "parser.h"
//#define DEBUGGING

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	int currentStatus = STATUS_INITIAL;
	int offset = transTable->offset;
	char currentChar = *(text + offset);
	int finish = 0;
	
	TRANSITION currentTransition;
	
	memset(token, 0, sizeof(TOKEN));
	
	while(!finish) {
		currentChar = *(text + offset);
        
#ifdef DEBUGGING
    printf("[%i][%c] -> ", currentStatus, currentChar);
#endif
		currentTransition = transTable->transitions[currentStatus][currentChar];
		
		if(currentTransition.function != NULL)
			currentTransition.function(&finish, token);
			
		currentStatus = currentTransition.nextStatus;
#ifdef DEBUGGING
    printf("%i\n", currentStatus);
#endif
		offset++;
	}
    
    transTable->offset += offset;
	
	return token;
}
