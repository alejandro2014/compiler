#include "transitionsTable.h"

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];
int numberStatus = 0;

TRANS_TABLE *newTransitionsTable() {
	TRANS_TABLE *table = (TRANS_TABLE *) malloc(sizeof(TRANS_TABLE));
	TRANSITION **transitions = (TRANSITION **) malloc(sizeof(TRANSITION *) * NUMBER_STATUS);
	TRANSITION *transitionsForAChar = NULL;
	TRANSITION *transition = NULL;
	int i, j;
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		transitionsForAChar = (TRANSITION *) malloc(sizeof(TRANSITION) * NUMBER_CHARS);
		
		for(j = 0; j < NUMBER_CHARS; j++) {
			transition = transitionsForAChar + j;
			transition->nextStatus = STATUS_ERROR;
			transition->function = giveTokenError;
		}
		
		transitions[i] = transitionsForAChar;
	}
	
	table->transitions = transitions;
	
	return table;
}

void deleteTransitionsTable(TRANS_TABLE **table) {
	TRANS_TABLE *table2 = *table;
	TRANSITION **transitions = table2->transitions;
	TRANSITION *current = NULL;
	int i, j;
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		current = transitions[i];
		free(current);
		current = NULL;
	}
	
	free(*table);
	*table = NULL;
}

void initializeTransitionsTable(TRANS_TABLE *transTable) {
	TRANSITION *transition = NULL;
	int i, j;
	
	for(i = 0; i < NUMBER_STATUS; i++) {
		for(j = 0; j < NUMBER_CHARS; j++) {
			transition = &transitionsTable[i][j]; 
			transition->nextStatus = STATUS_ERROR;
			transition->function = giveTokenError;
		}
	}
	
	addTransitions(transTable);
}

void addTransitions(TRANS_TABLE *transTable) {
	int i;
	
	for(i = 0x30; i < 0x40; i++)
		addTransition(transTable, STATUS_INITIAL, i, STATUS_READ_DIGIT, NULL);
			
	addTransition(transTable, STATUS_INITIAL, '-', STATUS_READ_DIGIT, NULL);
	
	//Strings
	addTransition(transTable, STATUS_INITIAL, '\"', STATUS_READ_STRING, NULL);
	
	for(i = 0; i < 256; i++)
		addTransition(transTable, STATUS_READ_STRING, i, STATUS_READ_STRING, NULL);
	
	addTransition(transTable, STATUS_READ_STRING, '\"', STATUS_GIVE_TOKEN, giveTokenString);
	
	addTransition(transTable, STATUS_INITIAL, 't', STATUS_READ_T, NULL);
	addTransition(transTable, STATUS_READ_T, 'r', STATUS_READ_R, NULL);
	addTransition(transTable, STATUS_READ_R, 'u', STATUS_READ_U, NULL);
	addTransition(transTable, STATUS_READ_U, 'e', STATUS_READ_E, NULL);
	
	addTransition(transTable, STATUS_INITIAL, 'f', STATUS_READ_F, NULL);
	addTransition(transTable, STATUS_READ_F, 'a', STATUS_READ_A, NULL);
	addTransition(transTable, STATUS_READ_A, 'l', STATUS_READ_L, NULL);
	addTransition(transTable, STATUS_READ_L, 's', STATUS_READ_S, NULL);
	addTransition(transTable, STATUS_READ_S, 'e', STATUS_READ_E, NULL);
	
	addTransition(transTable, STATUS_READ_E, 0x00, STATUS_GIVE_TOKEN, giveTokenBoolean);
	
	for(i = 0x30; i < 0x40; i++) 
		addTransition(transTable, STATUS_READ_DIGIT, i, STATUS_READ_DIGIT, NULL);
		
	addTransition(transTable, STATUS_READ_DIGIT, 0x00, STATUS_GIVE_TOKEN, giveTokenInt);
	
	for(i = 0; i < 256; i++) 
		addTransition(transTable, STATUS_GIVE_TOKEN, i, STATUS_GIVE_TOKEN, NULL);
}

void addKeyword(TRANS_TABLE *transTable, char *keyword, int tokenType) {
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
		addTransition(transTable, currentStatus, currentChar, nextStatus, NULL);
		currentStatus = nextStatus;
	}
	
	switch(tokenType) {
		case TOKEN_BOOLEAN: returnTokenFunction = giveTokenBoolean; break;
		case TOKEN_INTEGER: returnTokenFunction = giveTokenInt; break;
	}
	
	addTransition(transTable, currentStatus, 0x00, nextStatus, returnTokenFunction);
}

void addTransition(TRANS_TABLE *transTable,
				   int currentStatus,
				   char charRead,
				   int nextStatus,
				   functionTransition functionPointer) {
	TRANSITION *currentTransition = &transTable->transitions[currentStatus][charRead];
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
