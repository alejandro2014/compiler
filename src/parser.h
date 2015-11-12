#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
	int currentToken;
	TOKEN *tokens[100];
} PARSER;

void getParserTokens(PARSER *parser, char *string, TRANS_TABLE *table);
void addTokenToParser(TOKEN *token, PARSER *parser);
PARSER *initParser();
void deleteParser(PARSER *parser);

#endif
