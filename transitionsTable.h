#ifndef TRANSITIONS_TABLE_H
#define TRANSITIONS_TABLE_H

#include "parser.h"

void initializeTransitionsTable();
void addKeyword(char *keyword, int tokenType);
void addTransition(int currentStatus,
				   char charRead,
				   int nextStatus,
				   functionTransition functionPointer);

#endif
