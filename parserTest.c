#include "parserTest.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

void testCase() {
	initializeTransitionsTable();
	
	IShouldIdentifyAPositiveInt();
	IShouldIdentifyANegativeInt();
	ItShouldIdentifyABooleanTrue();
	ItShouldIdentifyABooleanFalse();
	itShouldIdentifyAString();
}

void IShouldIdentifyAPositiveInt() {
	char *integerText = "1234";
	TOKEN *token = NULL;
	
	token = parse(integerText);
	
	printf("I should identify a positive int - ");
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
}

void IShouldIdentifyANegativeInt() {
	char *integerText = "-1234";
	TOKEN *token = NULL;
	
	token = parse(integerText);
	
	printf("I should identify a negative int - ");
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
}

void ItShouldIdentifyABooleanTrue() {
	char *booleanText = "true";
	TOKEN *token = NULL;
	
	token = parse(booleanText);
	
	printf("I should identify a boolean true - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
}

void ItShouldIdentifyABooleanFalse() {
	char *booleanText = "false";
	TOKEN *token = NULL;
	
	token = parse(booleanText);
	
	printf("I should identify a boolean false - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
}

void itShouldIdentifyAString() {
	char *stringText = "\"A string is surrounded by double quotes\"";
	TOKEN *token = NULL;
	
	token = parse(stringText);
	
	printf("I should identify a string - ");
	assert(token->type == TOKEN_STRING);
	printf("OK\n");
}
