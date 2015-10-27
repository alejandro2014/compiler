#include "transitionsTable.h"

TRANS_TABLE *newTransitionsTable() {
	TRANS_TABLE *table = (TRANS_TABLE *) malloc(sizeof(TRANS_TABLE));
	int transitionsNo = NUMBER_CHARS * NUMBER_STATUS;
	TRANSITION *transitions = (TRANSITION *) malloc(sizeof(TRANSITION) * transitionsNo);
	TRANSITION *transition = NULL;
	int i;

	for(i = 0; i < transitionsNo; i++) {
		transition = transitions + i;
		transition->nextStatus = STATUS_ERROR;
		transition->function = &giveTokenError;
	}

	table->transitions = transitions;
  table->numberOfChars = NUMBER_CHARS;
  table->numberOfStatus = NUMBER_STATUS;
  table->maxStateAlloc = 0;
  table->offset = 0;
	table->takenStatusNo = 1;

	return table;
}

void deleteTransitionsTable(TRANS_TABLE *table) {
	free(table->transitions);
	free(table);
}

void addTransitions(TRANS_TABLE *transTable) {
    addNumbers(transTable);
		addStrings(transTable);
		addKeywords(transTable);
}

void addNumbers(TRANS_TABLE *transTable) {
	int readingDigit = transTable->takenStatusNo + 1;
	int i;

	for(i = 0x30; i < 0x40; i++) {
		addTransition(transTable, STATUS_INITIAL, i, readingDigit, NULL);
	}

  for(i = 0x30; i < 0x40; i++) {
		addTransition(transTable, readingDigit, i, readingDigit, NULL);
	}

	addFinalTransitions(transTable, readingDigit, TOKEN_INTEGER);

	transTable->takenStatusNo += 1;
}

void addStrings(TRANS_TABLE *transTable) {
	int openQuoteStatus = transTable->takenStatusNo + 1;
	int closeQuoteStatus = openQuoteStatus + 1;
	int i;

  addTransition(transTable, STATUS_INITIAL, '\"', openQuoteStatus, NULL);

	addTransition(transTable, openQuoteStatus, ' ', openQuoteStatus, NULL);
	addTransition(transTable, openQuoteStatus, '_', openQuoteStatus, NULL);

	for(i = 0x30; i < 0x40; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NULL);
	}

	for(i = 0x41; i < 0x5a; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NULL);
	}

	for(i = 0x61; i < 0x7a; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NULL);
	}

	addTransition(transTable, openQuoteStatus, '\"', closeQuoteStatus, NULL);
	addFinalTransitions(transTable, closeQuoteStatus, TOKEN_STRING);

	transTable->takenStatusNo += 2;
}

void addKeywords(TRANS_TABLE *transTable) {
    addKeyword(transTable, "true", TOKEN_BOOLEAN);
		addKeyword(transTable, "false", TOKEN_BOOLEAN);
}

void addKeyword(TRANS_TABLE *transTable, char *keyword, int tokenType) {
	int length = strlen(keyword);
	int i;
	char currentChar;
	int currentStatus = STATUS_INITIAL;
	int nextStatus = transTable->takenStatusNo + 1;

	for(i = 0; i < length; i++) {
		currentChar = *(keyword + i);

		addTransition(transTable, currentStatus, currentChar, nextStatus, NULL);

		currentStatus = nextStatus;
		nextStatus = currentStatus + 1;
	}

	transTable->takenStatusNo += length;

	addFinalTransitions(transTable, currentStatus, tokenType);
}

void addFinalTransitions(TRANS_TABLE *table, int currentStatus, int tokenType) {
	functionTransition returnTokenFunction = NULL;

	switch(tokenType) {
		case TOKEN_BOOLEAN: returnTokenFunction = giveTokenBoolean; break;
		case TOKEN_INTEGER: returnTokenFunction = giveTokenInt; break;
		case TOKEN_STRING: returnTokenFunction = giveTokenString; break;
	}

	addTransition(table, currentStatus, 0x00, STATUS_RETURNING, returnTokenFunction);
	addTransition(table, currentStatus, 0x20, STATUS_RETURNING, returnTokenFunction);
}

void addTransition(TRANS_TABLE *transTable, int currentStatus, char charRead, int nextStatus, functionTransition functionPointer) {
	TRANSITION *currentTransition = getTransition(transTable, currentStatus, charRead);

	printf("currStatus: %d charRead: %c %x nextStatus: %d functionPointer: %p\n", currentStatus, charRead, charRead, nextStatus, functionPointer);
	currentTransition->nextStatus = nextStatus;
	currentTransition->function = functionPointer;
}

TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead) {
	//printf("currentStatus: %d charRead: %c %d offset: %d\n", currentStatus, charRead, charRead, charRead * NUMBER_CHARS + currentStatus);
	return transTable->transitions + charRead * NUMBER_STATUS + currentStatus;
}

void giveTokenBoolean(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_BOOLEAN;
}

void giveTokenInt(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_INTEGER;
}

void giveTokenError(int *finish, TOKEN *token) {
	*finish = 1;
}

void giveTokenString(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_STRING;
}
