#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	int currentStatus = STATUS_INITIAL;
	int offset = transTable->offset;
	char currentChar = *(text + offset);
	int finish = 0;
	TRANSITION *currentTransition;

	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	memset(token, 0, sizeof(TOKEN));

	while(!finish) {
		currentChar = *(text + offset);

		currentTransition = transTable->transitions + currentChar * NUMBER_CHARS + currentStatus;

		if(currentTransition->function != NULL)
			currentTransition->function(&finish, token);

		currentStatus = currentTransition->nextStatus;

		offset++;
	}

  transTable->offset += offset;

	return token;
}
