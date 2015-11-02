#ifndef LEXER_H
#define LEXER_H

#include "transitionsTable.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text);
TOKEN *newToken();
char *getContentToken(char *text, int iniPos, int endPos, int tokenType);
void moveOffsetString(char *string, int *iniPos, int *endPos);
void moveOffsetInteger(char *string, int *offset);

#endif
