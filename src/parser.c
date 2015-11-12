#include "helper.h"
#include "parser.h"
#include "transitionsTable.h"

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

void getParserTokens(PARSER *parser, char *string, TRANS_TABLE *table) {
	TOKEN *token = NULL;
	int finish = 0;
	
	printf("[INFO] Parsing string:\n%s\n", string);
	
	while(!finish) {
		token = getToken(table, string);
		if(token == NULL) {
			finish = 1;
			continue;
		}
		
		addTokenToParser(token, parser);
	}	
}

void addTokenToParser(TOKEN *token, PARSER *parser) {
	int tokenNo = parser->currentToken;
	parser->tokens[tokenNo] = token;
	
	printf("Added token [%s] %s\n", getTokenName(token->type), token->content);
	
	parser->currentToken++;
}
