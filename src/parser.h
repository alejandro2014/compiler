#ifndef TOKEN_H
#define TOKEN_H

#include "transitionsTable.h"

TOKEN *parse(TRANS_TABLE *transTable, char *text);
char *getContentToken(char *text, int iniPos, int endPos, int tokenType);
void moveOffsetInteger(char *string, int *offset);

#endif
