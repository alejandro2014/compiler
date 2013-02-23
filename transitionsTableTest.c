#include "transitionsTableTest.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

void transitionsTableTestCase() {
	printf("transitionsTableTestCase\n");
	itShouldCreateTransitionsTable();
	itShouldDeleteTransitionsTable();
	itShouldInitializeTransitionsTable();
	itShouldAddAKeyWord();
	itShouldAddSeveralKeywords();
}

void itShouldCreateTransitionsTable() {
	TRANS_TABLE *table = newTransitionsTable();
	
	printf("\tIt should create a new transitions table - ");
	assert(table != NULL);
	assert(table->transitions != NULL);
	printf("OK\n");
	
	deleteTransitionsTable(table);
}

void itShouldDeleteTransitionsTable() {
	/*TRANS_TABLE *table = newTransitionsTable();
	
	deleteTransitionsTable(table);
	
	printf("\tIt should delete a transitions table - ");
	assert(table == NULL);
	printf("OK\n");*/
}

void itShouldInitializeTransitionsTable() {
	TRANS_TABLE *table = newTransitionsTable();
	
	printf("\tIt should initialize the transitions table - ");
	assert(table->transitions[2]['t'].nextStatus == STATUS_ERROR);
	printf("OK\n");
	
	deleteTransitionsTable(table);
}

void itShouldAddAKeyWord() {	
	TRANS_TABLE *table = newTransitionsTable();
	unsigned char *booleanText = "false";
	TOKEN *token = NULL;
	
	addKeyword(table, booleanText, TOKEN_BOOLEAN);
	token = parse(table, booleanText);
	
	printf("\tIt should add a keyword - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(table);
}

void itShouldAddSeveralKeywords() {
	TRANS_TABLE *table = newTransitionsTable();
	unsigned char *booleanText = "false";
	unsigned char *intText = "1234";
	TOKEN *token = NULL;
	
	addKeyword(table, booleanText, TOKEN_BOOLEAN);
	addKeyword(table, intText, TOKEN_INTEGER);
	
	printf("\tIt should add several keywords - ");
	token = parse(table, booleanText);
	assert(token->type == TOKEN_BOOLEAN);
	free(token);
	
	token = parse(table, intText);
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(table);
}

void transitionsTable_before() {
	//initializeTransitionsTable();
}
