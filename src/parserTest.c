#include "parserTest.h"

void parserTestCase() {
	printf("parserTestCase\n");
	//initializeTransitionsTable();
	
	IShouldIdentifyAPositiveInt();
	IShouldIdentifyANegativeInt();
	ItShouldIdentifyABooleanTrue();
	ItShouldIdentifyABooleanFalse();
	itShouldIdentifyAString();
    itShouldIdentifyTokensSeparatedBySpace();
}

void IShouldIdentifyAPositiveInt() {
	char *integerText = "1234";
	TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *token = parse(transTable, integerText);
	
	printf("\tI should identify a positive int - ");
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(transTable);
}

void IShouldIdentifyANegativeInt() {
	char *integerText = "-1234";
	TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *token = parse(transTable, integerText);
	
	printf("\tI should identify a negative int - ");
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(transTable);
}

void ItShouldIdentifyABooleanTrue() {
	char *booleanText = "true";
	TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *token = parse(transTable, booleanText);
	
	printf("\tI should identify a boolean true - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(transTable);
}

void ItShouldIdentifyABooleanFalse() {
	char *booleanText = "false";
	TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *token = parse(transTable, booleanText);
	
	printf("\tI should identify a boolean false - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(transTable);
}

void itShouldIdentifyAString() {
	char *stringText = "\"A string is surrounded by double quotes\"";
	TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *token = parse(transTable, stringText);
	
	printf("\tI should identify a string - ");
	assert(token->type == TOKEN_STRING);
	printf("OK\n");
	
	free(token);
	deleteTransitionsTable(transTable);
}

void itShouldIdentifyTokensSeparatedBySpace() {
    char *text = "1234 true";
    TRANS_TABLE *transTable = newTransitionsTable();
	addTransitions(transTable);
	TOKEN *tokenNumber = parse(transTable, text);
    TOKEN *tokenBoolean = parse(transTable, text);
	
	printf("\tI should identify tokens separated by space - ");
	assert(tokenNumber->type == TOKEN_INTEGER);
    assert(tokenBoolean->type == TOKEN_BOOLEAN);
	printf("OK\n");
	
	free(tokenNumber);
    free(tokenBoolean);
	deleteTransitionsTable(transTable);
}
