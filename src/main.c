#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "transitionsTable.h"
#include "grammar.h"

char *loadFile(char *path);
char *getTokenName(int tokenNumber);
void parseInput(char *inputString);

int main(int argn, char *argv[]) {
	GRAMMAR *grammar1 = createGrammar();
	
	return 0;
	//char *fileName = "/Users/alejandro/programs/compiler/testdata/menus.json";
	char *fileName = "/home/alejandro/programs/compiler/testdata/menus.json";
	char *string = loadFile(fileName);
	
	GRAMMAR *grammar = createGrammar();
	parseInput(string);
	
	return 0;
}

void parseInput(char *inputString) {
	TRANS_TABLE *table = newTransitionsTable();
	PARSER *parser = initParser();
	TOKEN *token = NULL;
	int finish = 0;
	
	addTransitions(table);
	printf("%s\n", inputString);
	
	while(!finish) {
		token = parse(table, inputString);
		if(token == NULL) {
			finish = 1;
			continue;
		}
		
		addTokenToParser(token, parser);
	}

	deleteParser(parser);
	deleteTransitionsTable(table);
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
