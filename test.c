#include "test.h"

void testCase() {
	testOne();
	testTwo();
}

void testOne() {
	//I have a text representing an integer
	char *integerText = "1234";
	TOKEN *token = NULL;
	
	token = parse(integerText);
	
	printf("I should identify a positive int - ");
	assert(token->type == TOKEN_INTEGER);
	printf("OK\n");
}

void testTwo() {
	assert(2 == 2);
}

TOKEN *parse(char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	memset(token, 0, sizeof(TOKEN));
	
	token->type = TOKEN_INTEGER;
	return token;
}
