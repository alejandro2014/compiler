#include "transitionsTable.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];
int numberStatus = 0;

TRANS_TABLE *newTransitionsTable() {
	TRANS_TABLE *table = (TRANS_TABLE *) malloc(sizeof(TRANS_TABLE));
	TRANSITION **transitions = (TRANSITION **) malloc(sizeof(TRANSITION *) * NUMBER_STATUS);
	TRANSITION *transitionsForAChar = NULL;
	TRANSITION *transition = NULL;
	int i, j;
	
	memset(table, 0, sizeof(TRANS_TABLE));
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		transitionsForAChar = (TRANSITION *) malloc(sizeof(TRANSITION) * NUMBER_CHARS);
		
		for(j = 0; j < NUMBER_CHARS; j++) {
			transition = transitionsForAChar + j; 
			transition->nextStatus = STATUS_ERROR;
			transition->function = giveTokenError;
		}
		
		*(transitions + i) = transitionsForAChar;
	}
	
	table->transitions = transitions;
	
	return table;
}

void deleteTransitionsTable(TRANS_TABLE *table) {
	TRANSITION *transitionsForAChar = NULL;
	int i, j;
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		transitionsForAChar = *(table->transitions + i);
		free(transitionsForAChar);
	}
	
	free(table);
	table = NULL;
}

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
	
	addTransitions();
}

void addTransitions() {
	int i;
	
	for(i = 0x30; i < 0x40; i++)
		addTransition(STATUS_INITIAL, i, STATUS_READ_DIGIT, NULL);
			
	addTransition(STATUS_INITIAL, '-', STATUS_READ_DIGIT, NULL);
	
	//Strings
	addTransition(STATUS_INITIAL, '\"', STATUS_READ_STRING, NULL);
	
	for(i = 0; i < 256; i++)
		addTransition(STATUS_READ_STRING, i, STATUS_READ_STRING, NULL);
	
	addTransition(STATUS_READ_STRING, '\"', STATUS_GIVE_TOKEN, giveTokenString);
	
	addTransition(STATUS_INITIAL, 't', STATUS_READ_T, NULL);
	addTransition(STATUS_READ_T, 'r', STATUS_READ_R, NULL);
	addTransition(STATUS_READ_R, 'u', STATUS_READ_U, NULL);
	addTransition(STATUS_READ_U, 'e', STATUS_READ_E, NULL);
	
	addTransition(STATUS_INITIAL, 'f', STATUS_READ_F, NULL);
	addTransition(STATUS_READ_F, 'a', STATUS_READ_A, NULL);
	addTransition(STATUS_READ_A, 'l', STATUS_READ_L, NULL);
	addTransition(STATUS_READ_L, 's', STATUS_READ_S, NULL);
	addTransition(STATUS_READ_S, 'e', STATUS_READ_E, NULL);
	
	addTransition(STATUS_READ_E, 0x00, STATUS_GIVE_TOKEN, giveTokenBoolean);
	
	for(i = 0x30; i < 0x40; i++) 
		addTransition(STATUS_READ_DIGIT, i, STATUS_READ_DIGIT, NULL);
		
	addTransition(STATUS_READ_DIGIT, 0x00, STATUS_GIVE_TOKEN, giveTokenInt);
	
	for(i = 0; i < 256; i++) 
		addTransition(STATUS_GIVE_TOKEN, i, STATUS_GIVE_TOKEN, NULL);
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
		numberStatus++;
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

void giveTokenBoolean(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_BOOLEAN;
}

void giveTokenInt(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_INTEGER;
}

void giveTokenError(int *finish, TOKEN *token) {
	*finish = 1;
}

void giveTokenString(int *finish, TOKEN *token) {
	*finish = 1;
	token->type = TOKEN_STRING;
}
