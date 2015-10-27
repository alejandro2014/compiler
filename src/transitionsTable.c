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
		addTransition(transTable, STATUS_INITIAL, i, readingDigit);
	}

  for(i = 0x30; i < 0x40; i++) {
		addTransition(transTable, readingDigit, i, readingDigit);
	}

	addFinalTransitions(transTable, readingDigit, TOKEN_INTEGER);

	transTable->takenStatusNo += 1;
}

void addStrings(TRANS_TABLE *transTable) {
	int openQuoteStatus = transTable->takenStatusNo + 1;
	int closeQuoteStatus = openQuoteStatus + 1;
	int i;

  addTransition(transTable, STATUS_INITIAL, '\"', openQuoteStatus);

	addTransition(transTable, openQuoteStatus, ' ', openQuoteStatus);
	addTransition(transTable, openQuoteStatus, '_', openQuoteStatus);

	for(i = 0x30; i < 0x40; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus);
	}

	for(i = 0x41; i < 0x5a; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus);
	}

	for(i = 0x61; i < 0x7a; i++) {
		addTransition(transTable, openQuoteStatus, i, openQuoteStatus);
	}

	addTransition(transTable, openQuoteStatus, '\"', closeQuoteStatus);
	addFinalTransitions(transTable, closeQuoteStatus, TOKEN_STRING);

	transTable->takenStatusNo += 2;
}

void addSpecialChars(TRANS_TABLE *table) {
		addSpecialChar(table, '{', TOKEN_CURLY_OPEN);
		addSpecialChar(table, '}', TOKEN_CURLY_CLOSE);
		addSpecialChar(table, '[', TOKEN_SQUARE_OPEN);
		addSpecialChar(table, ']', TOKEN_SQUARE_CLOSE);
		addSpecialChar(table, ':', TOKEN_COLON);
		addSpecialChar(table, ',', TOKEN_COMMA);
}

void addSpecialChar(TRANS_TABLE *table, char character, int tokenType) {
		addTransition(table, STATUS_INITIAL, character, STATUS_RETURNING);
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

		addTransition(transTable, currentStatus, currentChar, nextStatus);

		currentStatus = nextStatus;
		nextStatus = currentStatus + 1;
	}

	transTable->takenStatusNo += length;

	addFinalTransitions(transTable, currentStatus, tokenType);
}

void addFinalTransitions(TRANS_TABLE *table, int currentStatus, int tokenType) {
	addTransition(table, currentStatus, 0x00, STATUS_RETURNING);
	addTransition(table, currentStatus, 0x20, STATUS_RETURNING);
}

void addTransition(TRANS_TABLE *transTable, int currentStatus, char charRead, int nextStatus) {
	TRANSITION *currentTransition = getTransition(transTable, currentStatus, charRead);

	printf("currStatus: %d charRead: %c %x nextStatus: %d\n", currentStatus, charRead, charRead, nextStatus);
	currentTransition->nextStatus = nextStatus;
}

TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead) {
	return transTable->transitions + charRead * NUMBER_STATUS + currentStatus;
}
