#include "transitionsTable.h"

TRANS_TABLE *createTransitionsTable(char *lexerInputFile) {
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
    
    addTransitions(table);

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
    addSpecialChars(transTable);
    addNeutralChars(transTable);
}

void addFinalTransitions(TRANS_TABLE *table, int currentStatus, int tokenType) {
    addTransition(table, currentStatus, 0x00, STATUS_RETURNING, tokenType);
    addTransition(table, currentStatus, ' ', STATUS_RETURNING, tokenType);
    addTransition(table, currentStatus, '\n', STATUS_RETURNING, tokenType);
    addTransition(table, currentStatus, ',', STATUS_RETURNING, tokenType);
}

void addTransition(TRANS_TABLE *transTable, int currentStatus, char charRead, int nextStatus, int tokenReturned) {
    TRANSITION *currentTransition = getTransition(transTable, currentStatus, charRead);

    currentTransition->nextStatus = nextStatus;
    currentTransition->tokenReturned = tokenReturned;
}

TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead) {
    return transTable->transitions + charRead * NUMBER_STATUS + currentStatus;
}

void addNumbers(TRANS_TABLE *transTable) {
    int readingDigit = transTable->takenStatusNo + 1;
    int i;

    for(i = 0x30; i < 0x3a; i++) addTransition(transTable, STATUS_INITIAL, i, readingDigit, NO_TOKEN);
    for(i = 0x30; i < 0x3a; i++) addTransition(transTable, readingDigit, i, readingDigit, NO_TOKEN);

    addFinalTransitions(transTable, readingDigit, TOKEN_INTEGER);

    transTable->takenStatusNo += 1;
}

void addStrings(TRANS_TABLE *transTable) {
    int openQuoteStatus = transTable->takenStatusNo + 1;
    int closeQuoteStatus = openQuoteStatus + 1;
    int i;

    addTransition(transTable, STATUS_INITIAL, '\"', openQuoteStatus, NO_TOKEN);
    addTransition(transTable, openQuoteStatus, ' ', openQuoteStatus, NO_TOKEN);
    addTransition(transTable, openQuoteStatus, '_', openQuoteStatus, NO_TOKEN);

    for(i = 0x30; i < 0x3a; i++) addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NO_TOKEN);
    for(i = 0x41; i < 0x5a; i++) addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NO_TOKEN);
    for(i = 0x61; i < 0x7a; i++) addTransition(transTable, openQuoteStatus, i, openQuoteStatus, NO_TOKEN);

    addTransition(transTable, openQuoteStatus, '\"', STATUS_RETURNING, TOKEN_STRING);

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
        addTransition(transTable, currentStatus, currentChar, nextStatus, NO_TOKEN);
        currentStatus = nextStatus;
        nextStatus = currentStatus + 1;
    }

    transTable->takenStatusNo += length;

    addFinalTransitions(transTable, currentStatus, tokenType);
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
    addTransition(table, STATUS_INITIAL, character, STATUS_RETURNING, tokenType);
}

void addNeutralChars(TRANS_TABLE *table) {
    addTransition(table, STATUS_INITIAL, 0x20, STATUS_INITIAL, NO_TOKEN);
    addTransition(table, STATUS_INITIAL, 0x0a, STATUS_INITIAL, NO_TOKEN);
}
