#include "parser.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text) {
    int currentStatus = STATUS_INITIAL;
    int offset = transTable->offset;
    char currentChar = *(text + offset);
    int finish = 0;
    int lengthToken = 0;
    TRANSITION *currentTransition;
    char *trimmedToken;

    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    memset(token, 0, sizeof(TOKEN));

    while(currentStatus != STATUS_RETURNING) {
        currentChar = *(text + (offset++));
        //printf(">>> [%d] %c %x\n", offset - 1, currentChar, currentChar);

        if(currentChar == 0x00) {
            currentStatus = STATUS_RETURNING;
            continue;
        }

        if(currentChar == 0x0a || currentChar == 0x20) {
            transTable->offset++;
            continue;
        }

        currentTransition = getTransition(transTable, currentStatus, currentChar);
        //printf("> [%d, %c %x]\n", currentStatus, currentChar, currentChar);

        currentStatus = currentTransition->nextStatus;
    }  

    token->type = currentTransition->tokenReturned;
    
    if(token->type == TOKEN_STRING || token->type == TOKEN_INTEGER || token->type == TOKEN_BOOLEAN) {
        token->content = getContentToken(text, transTable->offset, offset, token->type);
    }
    
    if(token->type == TOKEN_INTEGER) {
        offset--;
    }

    transTable->offset = offset;

    return token;
}

char *getContentToken(char *text, int iniPos, int endPos, int tokenType) {
    switch(tokenType) {
        case TOKEN_STRING:
			moveOffsetString(text, &iniPos, &endPos);
            break;
        case TOKEN_INTEGER:
            moveOffsetInteger(text, &endPos);
            break;
    }
    
    int lengthToken = endPos - iniPos + 1;
    char *content = (char *) malloc(sizeof(char) * (lengthToken + 1));
    
    memset(content, 0, lengthToken + 1);
    
    //printf("cp - ini: %d %c, end: %d %c, length: %d\n", iniPos, *(text + iniPos), endPos, *(text + endPos), lengthToken);
    memcpy(content, text + iniPos, lengthToken);
    
    return content;
}

void moveOffsetString(char *string, int *iniPos, int *endPos) {
	int initial = *iniPos - 1;
	int final = *endPos;
	
	while(*(string + initial) != '\"') {
		//printf("r1 - [%d] %c %x\n", initial, *(string + initial), *(string + initial));
		initial++;
	}
	
	while(*(string + final) != '\"') {
		//printf("r2 - [%d] %c %x\n", final, *(string + final), *(string + final));
		final--;
	}
	
	*iniPos = initial + 1;
	*endPos = final - 1;
}

void moveOffsetInteger(char *string, int *offset) {
    int currentOffset = *offset;
    char currentChar = *(string + currentOffset);
    
    while(currentChar < 0x30 || currentChar > 0x39) {
        currentOffset--;
        currentChar = *(string + currentOffset);
    }
    
    *offset = currentOffset;
}
