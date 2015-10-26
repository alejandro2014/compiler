#include <stdio.h>
#include "parser.h"

int main(int argn, char **argv) {
	char *string = "false true";
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
