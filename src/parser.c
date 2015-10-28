#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
	int currentStatus = STATUS_INITIAL;
	int offset = transTable->offset;
	char currentChar = *(text + offset);
	int finish = 0;
	int lengthToken = 0;
	TRANSITION *currentTransition;
	char *trimmedToken;

	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	memset(token, 0, sizeof(TOKEN));

	while(currentStatus != STATUS_RETURNING) {
		currentChar = *(text + (offset++));

		if(currentChar == 0x00) {
			currentStatus = STATUS_RETURNING;
			continue;
		}

		if(currentChar == 0x0a || currentChar == 0x20) {
				transTable->offset++;
				continue;
		}

		currentTransition = getTransition(transTable, currentStatus, currentChar);
		//printf("> [%d, %c %x]\n", currentStatus, currentChar, currentChar);

		currentStatus = currentTransition->nextStatus;
	}

	token->type = currentTransition->tokenReturned;

	if(token->type == TOKEN_STRING || token->type == TOKEN_INTEGER || token->type == TOKEN_BOOLEAN) {
		if(token->type == TOKEN_INTEGER) {
			lengthToken = offset - transTable->offset;
		} else {
			lengthToken = offset - transTable->offset + 1;
		}

		token->content = (char *) malloc(sizeof(char) * lengthToken);
		memset(token->content, 0, lengthToken);
		memcpy(token->content, text + transTable->offset, lengthToken - 1);
	}

  transTable->offset = offset;

	return token;
}
