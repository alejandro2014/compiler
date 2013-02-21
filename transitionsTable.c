#include "transitionsTable.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];
int numberStatus = 0;

void initializeTransitionsTable() {
	TRANSITION *transition = NULL;
	int i, j;
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		for(j = 0; j < NUMBER_CHARS; j++) {
			transition = &transitionsTable[i][j]; 
			transition->nextStatus = STATUS_ERROR;
			transition->function = giveTokenError;
		}
	}
	
	//addTransitions();
}

void addKeyword(char *keyword, int tokenType) {
	int length = strlen(keyword);
	int i;
	char currentChar;
	int currentStatus = STATUS_INITIAL;
	int nextStatus;
	functionTransition returnTokenFunction = NULL;
	
	for(i = 0; i < length; i++) {
		currentChar = *(keyword + i);
		
		nextStatus = currentStatus + 1;
		addTransition(currentStatus, currentChar, nextStatus, NULL);
		currentStatus = nextStatus;
	}
	
	switch(tokenType) {
		case TOKEN_BOOLEAN: returnTokenFunction = giveTokenBoolean; break;
		case TOKEN_INTEGER: returnTokenFunction = giveTokenInt; break;
	}
	
	addTransition(currentStatus, 0x00, nextStatus, returnTokenFunction);
}

void addTransition(int currentStatus,
				   char charRead,
				   int nextStatus,
				   functionTransition functionPointer) {
	TRANSITION *currentTransition = &transitionsTable[currentStatus][charRead];
	currentTransition->nextStatus = nextStatus;
	currentTransition->function = functionPointer;
}
