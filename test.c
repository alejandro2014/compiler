#include "test.h"
#include "token.h"

void testCase() {
	IShouldIdentifyAPositiveInt();
	IShouldIdentifyANegativeInt();
	ItShouldIdentifyABooleanTrue();
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
	char *integerText = "true";
	TOKEN *token = NULL;
	
	token = parse(integerText);
	
	printf("I should identify a boolean true - ");
	assert(token->type == TOKEN_BOOLEAN);
	printf("OK\n");
}
