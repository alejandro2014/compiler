#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	int currentStatus = STATUS_INITIAL;
	int offset = transTable->offset;
	char currentChar = *(text + offset);
	int finish = 0;
	TRANSITION *currentTransition;

  printf("Starting at position %d\n", offset);
	
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	memset(token, 0, sizeof(TOKEN));

	while(!finish) {
		currentChar = *(text + offset);
		printf(">> %c\n", currentChar);

		currentTransition = getTransition(transTable, currentStatus, currentChar);

		if(currentTransition->function != NULL) {
			currentTransition->function(&finish, token);
		}

		currentStatus = currentTransition->nextStatus;
		offset++;
	}

  transTable->offset += offset;

	return token;
}
