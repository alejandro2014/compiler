#include "grammar.h"

GRAMMAR *createGrammar() {
    countWords("This is a nice string");
	/*GRAMMAR *grammar = (GRAMMAR *) malloc(sizeof(GRAMMAR));
	memset(grammar, 0, sizeof(GRAMMAR));
    
    grammar->rules = (GRAMMAR_RULE *) malloc(MAX_RULES * sizeof(GRAMMAR_RULE));
    memset(grammar->rules, 0, MAX_RULES * sizeof(GRAMMAR_RULE));
	
	addGrammarRule(grammar, "object", "{ }");
	addGrammarRule(grammar, "object", "{ members }");
	addGrammarRule(grammar, "members", "pair");
	addGrammarRule(grammar, "members", "pair , members");
	addGrammarRule(grammar, "pair", "string : value");
	
	addGrammarRule(grammar, "array", "[ ]");
	addGrammarRule(grammar, "array", "[ elements ]");
	addGrammarRule(grammar, "elements", "value");
	addGrammarRule(grammar, "elements", "value , elements");
	addGrammarRule(grammar, "value", "string");
	
	addGrammarRule(grammar, "value", "number");
	addGrammarRule(grammar, "value", "object");
	addGrammarRule(grammar, "value", "array");
	addGrammarRule(grammar, "value", "true");
	addGrammarRule(grammar, "value", "false");
	
	return grammar;*/
    return NULL;
}

/*void addGrammarRule(GRAMMAR *grammar, char *ruleName, char *rules) {
	int position = grammar->ruleNo;
	GRAMMAR_RULE *rule = grammar->rules + position;
	
	rule->ruleName = ruleName;
    rule->rules = allocateRules(rules);
	
	grammar->ruleNo++;
}

char *allocateRules(char *string) {
    int wordsNo = countWords(string);
    char **rules = (char *) malloc(wordsNo * sizeof(char *));
    memset(rules, 0, wordsNo * sizeof(char *));
    int i;
    
    for(i = 0; i < wordsNo; i++) {
    
    }
}*/

void countWords(char *string) {
    int length = strlen(string);
    int spacesNo = 0;
    int i, j;
    int iniPos = 0;
    int finPos = 0;
    
    for(i = 0; i < length + 1; i++) {
        if(*(string + i) == 0x20 || *(string + i) == 0x00) {
            finPos = i;
            
            newWord(string, iniPos, finPos);
            
            iniPos = finPos + 1;
        }
    }
}

char *newWord(char *string, int initialPos, int finalPos) {
    int j;
    
    for(j = initialPos; j < finalPos; j++) {
        printf("%c", *(string + j));
    }
    
    printf(">\n");
    return NULL;
}
