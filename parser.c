#include "parser.h"

TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

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

TOKEN *parse(char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	int currentStatus = STATUS_INITIAL;
	int offset = 0;
	char currentChar = *(text + offset);
	int finish = 0;
	
	TRANSITION currentTransition;
	
	memset(token, 0, sizeof(TOKEN));
	
	while(!finish) {
		currentChar = *(text + offset);
		currentTransition = transitionsTable[currentStatus][currentChar];
		
		if(currentTransition.function != NULL)
			currentTransition.function(&finish, token);
			
		currentStatus = currentTransition.nextStatus;
		offset++;
	}
	
	return token;
}
