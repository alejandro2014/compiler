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

	while(currentStatus != STATUS_RETURNING) {
		currentChar = *(text + offset);
		printf(">> %c\n", currentChar);

		currentTransition = getTransition(transTable, currentStatus, currentChar);
		currentStatus = currentTransition->nextStatus;
		offset++;
	}

  transTable->offset = offset;

	return token;
}
