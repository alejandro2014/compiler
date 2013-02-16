#include "test.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

void testCase() {
	itShouldSetAProperTransition();
	IShouldIdentifyAPositiveInt();
	IShouldIdentifyANegativeInt();
	ItShouldIdentifyABooleanTrue();
	ItShouldIdentifyABooleanFalse();
}

void itShouldSetAProperTransition() {
	addTransition(0, 'b', 2, NULL);
	printf("It should set a proper transition - ");
	assert(transitionsTable[0]['b'].nextStatus == 2);
	printf("OK\n");
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

