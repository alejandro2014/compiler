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
        token->content = getContentToken(text, transTable->offset, offset);
    }

    transTable->offset = offset;

    return token;
}

char *getContentToken(char *text, int iniPos, int endPos) {
    int lengthToken = endPos - iniPos;
    char *content = (char *) malloc(sizeof(char) * lengthToken);
    
    memset(content, 0, lengthToken);
    memcpy(content, text + iniPos, lengthToken - 1);
    
    return content;
}
