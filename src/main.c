/*
# Comment in the JSON

{
	[
		"menu": {
			"coords": {
				"x": 23,
				"y": 45,
				"height": 10,
				"width": 20
			}
		},
		"menu2": {
			...
		}
	]
}
*/
#include <stdio.h>
#include "parser.h"

char *readJsonFile(char *path);
char *getTokenName(int tokenNumber);

int main(int argn, char **argv) {
	char *fileName = "menus.json";
	char *string = readJsonFile(fileName);
	int tokensNo = 7;
	TRANS_TABLE *table = newTransitionsTable();
	TOKEN *token = NULL;
	int i;

	addTransitions(table);

	for(i = 0; i < tokensNo; i++) {
		token = parse(table, string);
		printf("[%s] ", getTokenName(token->type));

		if(token->content) {
			printf(" %s", token->content);
		}

		printf("\n");
	}

	deleteTransitionsTable(table);
	return 0;
}

char *readJsonFile(char *path) {
	return "1234 true {{\"A nice string\" false 1234";
}

char *getTokenName(int tokenNumber) {
	char *name = "";

	switch(tokenNumber) {
		case NO_TOKEN: name = "No token"; break;
		case TOKEN_INTEGER: name = "Integer"; break;
		case TOKEN_BOOLEAN: name = "Boolean"; break;
		case TOKEN_STRING: name = "String"; break;
		case TOKEN_CURLY_OPEN: name = "Curly {"; break;
		case TOKEN_CURLY_CLOSE: name = "Curly }"; break;
		case TOKEN_SQUARE_OPEN: name = "Square ["; break;
		case TOKEN_SQUARE_CLOSE: name = "Square ]"; break;
		case TOKEN_COLON: name = "Colon ':'"; break;
		case TOKEN_COMMA: name = "Comma ','"; break;
	}

	return name;
}
