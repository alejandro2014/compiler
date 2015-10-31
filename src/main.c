#include <stdio.h>
#include "parser.h"

char *loadFile(char *path);
char *getTokenName(int tokenNumber);

int main(int argn, char **argv) {
	//char *fileName = "/Users/alejandro/programs/compiler/testdata/menus.json";
	char *fileName = "/home/alejandro/programs/compiler/testdata/menus.json";
	char *string = loadFile(fileName);
	TRANS_TABLE *table = newTransitionsTable();
	TOKEN *token = NULL;
	int finish = 0;

	printf("%s\n", string);
	addTransitions(table);

	while(!finish) {
		token = parse(table, string);
		if(token == NULL) {
			finish = 1;
			continue;
		}
		
		printf("[%s] %s\n", getTokenName(token->type), token->content);
	}

	deleteTransitionsTable(table);
	return 0;
}

char *loadFile(char *path) {
	char *buffer;
	int fileSize;

	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	buffer = (char *) malloc(sizeof(char) * fileSize);
	fseek(file, 0, SEEK_SET);
	fread(buffer, 1, fileSize, file);
	fclose(file);

	return buffer;
}

char *getTokenName(int tokenNumber) {
	char *name = "";

	switch(tokenNumber) {
		case NO_TOKEN:           name = "NO TOKEN "; break;
		case TOKEN_INTEGER:      name = "Integer  "; break;
		case TOKEN_BOOLEAN:      name = "Boolean  "; break;
		case TOKEN_STRING:       name = "String   "; break;
		case TOKEN_CURLY_OPEN:   name = "Curly {  "; break;
		case TOKEN_CURLY_CLOSE:  name = "Curly }  "; break;
		case TOKEN_SQUARE_OPEN:  name = "Square [ "; break;
		case TOKEN_SQUARE_CLOSE: name = "Square ] "; break;
		case TOKEN_COLON:        name = "Colon ':'"; break;
		case TOKEN_COMMA:        name = "Comma ','"; break;
	}

	return name;
}
