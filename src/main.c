#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "transitionsTable.h"
#include "grammar.h"

void parseInput(char *inputString, TRANS_TABLE *table, GRAMMAR *grammar);

//char *INPUT_PATH_MAC = "/Users/alejandro/programs/compiler/testdata/menus.json";
char *INPUT_PATH_LINUX = "/home/alejandro/programs/compiler/testdata/menus.json";
char *GRAMMAR_PATH = "/home/alejandro/programs/compiler/testdata/grammar.txt";
char *LEXER_FILE_PATH = "";

int main(int argn, char *argv[]) {
	char *string = loadFile(INPUT_PATH_LINUX);
	
	TRANS_TABLE *transTable = createTransitionsTable(LEXER_FILE_PATH);
	GRAMMAR *grammar = createGrammar(GRAMMAR_PATH);
	
	GRAMMAR_RULE **grammarRules = (GRAMMAR_RULE **) malloc(grammar->ruleNo * sizeof(GRAMMAR_RULE *));
	memset(grammarRules, 0, sizeof(grammar->ruleNo *sizeof(GRAMMAR_RULE *)));
	
	parseInput(string, transTable, grammar);
	//lookupRule("value", grammar, grammarRules);
	
	//lookupRule("objec", grammar, grammarRules);
	return 0;
}

void parseInput(char *inputString, TRANS_TABLE *table, GRAMMAR *grammar) {
	PARSER *parser = initParser();
	TOKEN *token = NULL;
	int finish = 0;
	
	printf("%s\n", inputString);
	
	while(!finish) {
		token = getToken(table, inputString);
		if(token == NULL) {
			finish = 1;
			continue;
		}
		
		addTokenToParser(token, parser);
	}

	deleteParser(parser);
	deleteTransitionsTable(table);
}
