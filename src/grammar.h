#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RULES 15

typedef struct {
	char *ruleName;
	char **names;
} GRAMMAR_RULE;

typedef struct {
	int ruleNo;
	GRAMMAR_RULE *rules;
} GRAMMAR;

GRAMMAR *createGrammar();
void addGrammarRule(GRAMMAR *grammar, char *ruleName, char *rulesString);
char **allocateRules(char *string);
char *getRuleName(char *string, int initialPos, int finalPos);

#endif
