#include "grammar.h"

GRAMMAR *createGrammar(char *grammarPath) {
    int numberOfRules = 15;
	GRAMMAR *grammar = (GRAMMAR *) malloc(sizeof(GRAMMAR));
	memset(grammar, 0, sizeof(GRAMMAR));
    
    grammar->rules = (GRAMMAR_RULE *) malloc(numberOfRules * sizeof(GRAMMAR_RULE));
    memset(grammar->rules, 0, numberOfRules * sizeof(GRAMMAR_RULE));
	
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
	
	return grammar;
}

void addGrammarRule(GRAMMAR *grammar, char *ruleName, char *rulesString) {
	int position = grammar->ruleNo;
	GRAMMAR_RULE *rule = grammar->rules + position;
	
	rule->ruleName = ruleName;
    rule->names = allocateRules(rulesString);
    
    int i = 0;
    
    printf("%s -> ", rule->ruleName);
    for(i = 0; i < 15; i++) {
        if(*(rule->names + i))
            printf("%s ", *(rule->names + i));
    }
    printf("\n");
	
	grammar->ruleNo++;
}

char **allocateRules(char *string) {
    int length = strlen(string);
    int spacesNo = 0;
    int i, j;
    int iniPos = 0;
    int finPos = 0;
    char *rule = NULL;
    int ruleNumber = 0;
    
    char **rules = (char **) malloc(MAX_RULES * sizeof(GRAMMAR_RULE *));
    memset(rules, 0, MAX_RULES * sizeof(GRAMMAR_RULE *));
    
    for(i = 0; i < length + 1; i++) {
        if(*(string + i) == 0x20 || *(string + i) == 0x00) {
            finPos = i;
            *(rules + ruleNumber) = getRuleName(string, iniPos, finPos);
            iniPos = finPos + 1;
            ruleNumber++;
        }
    }
    
    return rules;
}

char *getRuleName(char *string, int initialPos, int finalPos) {
    int lengthString = (finalPos - initialPos + 1) * sizeof(char);
    char *ruleComponent = (char *) malloc(lengthString);
    
    memcpy(ruleComponent, string + initialPos, lengthString - 1);
    *(ruleComponent + lengthString - 1) = 0x00;
    
    return ruleComponent;
}

GRAMMAR_RULE lookupRule() {
    
}
