#include "transitionsTableTest.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

void transitionsTableTestCase() {
	printf("transitionsTableTestCase\n");
	itShouldInitializeTransitionsTable();
	itShouldAddAKeyWord();
	itShouldAddSeveralKeywords();
}

void itShouldInitializeTransitionsTable() {
	transitionsTable_before();
	
	printf("\tIt should initialize the transitions table - ");
	assert(transitionsTable[2]['t'].nextStatus == STATUS_ERROR);
	printf("OK\n");
}

void itShouldAddAKeyWord() {
	transitionsTable_before();
	
	addKeyword("false", TOKEN_BOOLEAN);
	
	char *booleanText = "false";
	TOKEN *token = parse(booleanText);
	
	printf("\tI should add a keyword - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
}

void itShouldAddSeveralKeywords() {
	transitionsTable_before();
	
	char *booleanText = "false";
	char *intText = "1234";
	TOKEN *token = NULL;
	
	addKeyword(booleanText, TOKEN_BOOLEAN);
	addKeyword(intText, TOKEN_INTEGER);
	
	printf("\tI should add several keywords - ");
	token = parse(booleanText);
	assert(token->type == TOKEN_BOOLEAN);
	
	token = parse(intText);
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
}

void transitionsTable_before() {
	initializeTransitionsTable();
}
