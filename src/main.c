/*
# Comment in the JSON

{
	[
		"menu": {
			"coords" {
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

int main(int argn, char **argv) {
	char *string = "1234 true \"A nice string\" false 1234";
	int tokensNo = 5;
	TRANS_TABLE *table = newTransitionsTable();
	TOKEN *token = NULL;
	int i;

	addKeyword(table, "true", TOKEN_BOOLEAN);
	addKeyword(table, "false", TOKEN_BOOLEAN);

	addStrings(table);
	addNumbers(table);

	for(i = 0; i < tokensNo; i++) {
		token = parse(table, string);
		printf("Token type: %d\n", token->type);
	}

	deleteTransitionsTable(table);
	return 0;
}
