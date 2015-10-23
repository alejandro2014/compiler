#include "transitionsTable.h"

TRANS_TABLE *newTransitionsTable() {
	TRANS_TABLE *table = (TRANS_TABLE *) malloc(sizeof(TRANS_TABLE));
	int transitionsNo = NUMBER_CHARS * NUMBER_STATUS;
	TRANSITION *transitions = (TRANSITION *) malloc(sizeof(TRANSITION) * transitionsNo);
	//TRANSITION *transitionsForAChar = NULL;
	TRANSITION *transition = NULL;
	int i, j;

	for(i = 0; i < transitionsNo; i++) {
		transition = transitions + i;
		transition->nextStatus = STATUS_ERROR;
		transition->function = giveTokenError;
		//transitionsForAChar = (TRANSITION *) malloc(sizeof(TRANSITION) * NUMBER_CHARS);
		//*(transitions + i) = transitionsForAChar;
	}

	table->transitions = transitions;
  table->numberOfChars = NUMBER_CHARS;
  table->numberOfStatus = NUMBER_STATUS;
  table->maxStateAlloc = 0;
  table->offset = 0;

	printf("Allocated table with %d statuses\n", transitionsNo);
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
    int i;

    for(i = 0x30; i < 0x40; i++)
			addTransition(transTable, STATUS_INITIAL, i, STATUS_READ_DIGIT, NULL);

		addTransition(transTable, STATUS_INITIAL, '-', STATUS_READ_DIGIT, NULL);

    for(i = 0x30; i < 0x40; i++)
			addTransition(transTable, STATUS_READ_DIGIT, i, STATUS_READ_DIGIT, NULL);

		addTransition(transTable, STATUS_READ_DIGIT, 0x00, STATUS_GIVE_TOKEN, giveTokenInt);
    addTransition(transTable, STATUS_READ_DIGIT, 0x20, STATUS_GIVE_TOKEN, giveTokenInt);
}

void addStrings(TRANS_TABLE *transTable) {
    int i;

    addTransition(transTable, STATUS_INITIAL, '\"', STATUS_READ_STRING, NULL);

	for(i = 0; i < 256; i++)
		addTransition(transTable, STATUS_READ_STRING, i, STATUS_READ_STRING, NULL);

	addTransition(transTable, STATUS_READ_STRING, '\"', STATUS_GIVE_TOKEN, giveTokenString);
}

void addKeywords(TRANS_TABLE *transTable) {
    addKeyword(transTable, "true", TOKEN_BOOLEAN);
		addKeyword(transTable, "false", TOKEN_BOOLEAN);
}

void addKeyword(TRANS_TABLE *transTable, char *keyword, int tokenType) {
	int length = strlen(keyword);
	int i;
	unsigned char currentChar;
	int currentStatus = STATUS_INITIAL;
	int nextStatus;
	functionTransition returnTokenFunction = NULL;

	for(i = 0; i < length; i++) {
		currentChar = *(keyword + i);

		nextStatus = ++(transTable->maxStateAlloc);
		addTransition(transTable, currentStatus, currentChar, nextStatus, NULL);
		currentStatus = nextStatus;
	}

	switch(tokenType) {
		case TOKEN_BOOLEAN: returnTokenFunction = giveTokenBoolean; break;
		case TOKEN_INTEGER: returnTokenFunction = giveTokenInt; break;
	}

	addTransition(transTable, currentStatus, 0x00, nextStatus, returnTokenFunction);
    addTransition(transTable, currentStatus, 0x20, nextStatus, returnTokenFunction);
}

void addTransition(TRANS_TABLE *transTable, int currentStatus, char charRead, int nextStatus, functionTransition functionPointer) {
	TRANSITION *currentTransition = getTransition(transTable, currentStatus, charRead);

	//printf("currStatus: %d charRead: %c nextStatus: %d\n", currentStatus, charRead, nextStatus);
	currentTransition->nextStatus = nextStatus;
	currentTransition->function = functionPointer;
}

TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead) {
	printf("currentStatus: %d charRead: %c %d offset: %d\n", currentStatus, charRead, charRead, charRead * NUMBER_CHARS + currentStatus);
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
