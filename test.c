#include "test.h"

void testCase() {
	IShouldIdentifyAPositiveInt();
	IShouldIdentifyANegativeInt();
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

TOKEN *parse(char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	memset(token, 0, sizeof(TOKEN));
	
	token->type = TOKEN_INTEGER;
	return token;
}
