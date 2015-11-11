#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "transitionsTable.h"
#include "grammar.h"

char *loadFile(char *path);
char *getTokenName(int tokenNumber);
void parseInput(char *inputString, TRANS_TABLE *table, GRAMMAR *grammar);

//char *INPUT_PATH_MAC = "/Users/alejandro/programs/compiler/testdata/menus.json";
char *INPUT_PATH_LINUX = "/home/alejandro/programs/compiler/testdata/menus.json";
char *GRAMMAR_PATH =  "/home/alejandro/programs/compiler/testdata/grammar.txt"

int main(int argn, char *argv[]) {
	char *string = loadFile(INPUT_PATH_LINUX);
	
	TRANS_TABLE *transTable = newTransitionsTable();
	GRAMMAR *grammar = createGrammar(GRAMMAR_PATH);
	
	parseInput(string, transTable, grammar);
	
	return 0;
}

void parseInput(char *inputString, TRANS_TABLE *table, GRAMMAR *grammar) {
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
