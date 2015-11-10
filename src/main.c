#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "transitionsTable.h"

char *loadFile(char *path);
char *getTokenName(int tokenNumber);
void parseInput(char *inputString);

typedef struct {
	char *ruleName;
	char **names;
} GRAMMAR_RULE;

typedef struct {
	int ruleNo;
	GRAMMAR_RULE rules[15];
} GRAMMAR;

GRAMMAR *createGrammar();
void addGrammarRule(GRAMMAR *grammar, char *ruleName, char *rules);

int main(int argn, char **argv) {
	char string1[] = "This is a string to delimit";
	char *newToken = "";
	
	newToken = strtok(string1, " ");
	printf("%s\n", newToken);
	while((newToken = strtok(NULL, " ")) != NULL) {
		printf("%s\n", newToken);
	}
	
	return 0;
	//char *fileName = "/Users/alejandro/programs/compiler/testdata/menus.json";
	char *fileName = "/home/alejandro/programs/compiler/testdata/menus.json";
	char *string = loadFile(fileName);
	
	GRAMMAR *grammar = createGrammar();
	parseInput(string);
	
	return 0;
}

GRAMMAR *createGrammar() {
	GRAMMAR *grammar = (GRAMMAR *) malloc(sizeof(GRAMMAR));
	memset(grammar, 0, sizeof(GRAMMAR));
	
	addGrammarRule(grammar, "object", "{ }");
	addGrammarRule(grammar, "object", "{ members }");
	addGrammarRule(grammar, "members", "pair");
	addGrammarRule(grammar, "members", "pair , members");
	addGrammarRule(grammar, "pair", "string : value");
	
	addGrammarRule(grammar, "array", "[ ]");
	addGrammarRule(grammar, "array", "[ elements ]");
	addGrammarRule(grammar, "elements", " value");
	addGrammarRule(grammar, "elements", "value , elements");
	addGrammarRule(grammar, "value", "string");
	
	addGrammarRule(grammar, "value", "number");
	addGrammarRule(grammar, "value", "object");
	addGrammarRule(grammar, "value", "array");
	addGrammarRule(grammar, "value", "true");
	addGrammarRule(grammar, "value", "false");
	
	return grammar;
}

void addGrammarRule(GRAMMAR *grammar, char *ruleName, char *rules) {
	/*int position = grammar->ruleNo;
	GRAMMAR_RULE *rule = grammar->rules[position];
	
	rule->nameRule = ruleName;
	
	grammar->ruleNo++;*/
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
