#include "lexer.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
    int currentStatus = STATUS_INITIAL;
    int offset = transTable->offset;
    char currentChar;
    int finish = 0;
    int lengthToken = 0;
    TRANSITION *currentTransition;
    char *trimmedToken;
    int eof = 0;
	TOKEN *token = newToken();
    
    while(currentStatus != STATUS_RETURNING) {
        currentChar = *(text + (offset++));

        if(currentChar == 0x00) {
            currentStatus = STATUS_RETURNING;
            printf("EOF reached\n");
            eof = 1;
            continue;
        }

        if(currentChar == 0x0a || currentChar == 0x20) {
            transTable->offset++;
            continue;
        }

        currentTransition = getTransition(transTable, currentStatus, currentChar);
        currentStatus = currentTransition->nextStatus;
    }  

	if(eof) return NULL;
	
	token->type = currentTransition->tokenReturned;
    token->content = getContentToken(text, transTable->offset, offset, token->type);
    
    if(token->type == TOKEN_INTEGER) {
        offset--;
    }

    transTable->offset = offset;

    return token;
}

TOKEN *newToken() {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    memset(token, 0, sizeof(TOKEN));
    return token;
}

char *getContentToken(char *text, int iniPos, int endPos, int tokenType) {
	char *content = NULL;
	
	if(tokenType == TOKEN_STRING || tokenType == TOKEN_INTEGER || tokenType == TOKEN_BOOLEAN) {
		switch(tokenType) {
			case TOKEN_STRING:
				moveOffsetString(text, &iniPos, &endPos);
				break;
			case TOKEN_INTEGER:
				moveOffsetInteger(text, &endPos);
				break;
		}
		
		int lengthToken = endPos - iniPos + 1;
		content = (char *) malloc(sizeof(char) * (lengthToken + 1));
		
		memset(content, 0, lengthToken + 1);
		memcpy(content, text + iniPos, lengthToken);
	}
    
    return content;
}

/*
Moves the beginning and end of the string in order to avoid the quotes
*/
void moveOffsetString(char *string, int *iniPos, int *endPos) {
	int initial = *iniPos - 1;
	int final = *endPos;
	
	while(*(string + initial) != '\"') initial++;
	while(*(string + final) != '\"') final--;
	
	*iniPos = initial + 1;
	*endPos = final - 1;
}

/*
Moves the offset of the integer in order to avoid the trailing comma
*/
void moveOffsetInteger(char *string, int *offset) {
    int currentOffset = *offset;
    char currentChar = *(string + currentOffset);
    
    while(currentChar < 0x30 || currentChar > 0x39) {
        currentOffset--;
        currentChar = *(string + currentOffset);
    }
    
    *offset = currentOffset;
}
