#include "transitionsTable.h"
#include "parser.h"

PARSER *initParser() {
	PARSER *parser = (PARSER *) malloc(sizeof(PARSER));
	memset(parser, 0, sizeof(PARSER));
	return parser;
}

//TODO Not very well defined function
void deleteParser(PARSER *parser) {
	TOKEN *currentToken;
	int i;
	
	for(i = 0; i < 100; i++) {
		currentToken = parser->tokens[i];
		
		if(currentToken) {
			if(currentToken->content) {
				free(currentToken->content);
			}
			
			free(currentToken);
		}
	}
	
	free(parser);
}

void addTokenToParser(TOKEN *token, PARSER *parser) {
	int tokenNo = parser->currentToken;
	parser->tokens[tokenNo] = token;
	
	//printf("[%s] %s\n", getTokenName(token->type), token->content);
	
	parser->currentToken++;
}
