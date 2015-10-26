#include <stdio.h>
#include "parser.h"

int main(int argn, char **argv) {
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
	char *string = "true false";
	TRANS_TABLE *table = newTransitionsTable();
	TOKEN *token = NULL;

	addKeyword(table, "true", TOKEN_BOOLEAN);
	addKeyword(table, "false", TOKEN_BOOLEAN);
	addNumbers(table);

	token = parse(table, string);
	printf("Token type: %d\n", token->type);

	token = parse(table, string);
	printf("Token type: %d\n", token->type);

	deleteTransitionsTable(table);
	return 0;
}
