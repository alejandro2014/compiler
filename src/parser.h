#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
	int tokensNo;
	int currentToken;
	TOKEN *tokens[100];
} PARSER;

void addTokenToParser(TOKEN *token, PARSER *parser);
PARSER *initParser();
void deleteParser(PARSER *parser);

#endif
