#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	int currentStatus = STATUS_INITIAL;
	int offset = transTable->offset;
	char currentChar = *(text + offset);
	int finish = 0;
	int lengthToken = 0;
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

	token->type = currentTransition->tokenReturned;
	if(token->type == TOKEN_STRING || token->type == TOKEN_INTEGER) {
		lengthToken = offset - transTable->offset + 1;
		token->content = (char *) malloc(sizeof(char) * lengthToken);
		memset(token->content, 0, lengthToken);
		memcpy(token->content, text + transTable->offset, lengthToken - 1);
	}

  transTable->offset = offset;

	return token;
}
