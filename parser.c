#include "parser.h"

static TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

void initializeTransitionsTable() {
	//addTransition(STATUS_INITIAL, 0x29, STATUS_READ_DIGIT, NULL);
}

void addTransition(int currentStatus,
				   char charRead,
				   int nextStatus,
				   char *functionPointer) {
	transitionsTable[currentStatus][charRead].nextStatus = nextStatus;
}

TOKEN *parse(char *text) {
	TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
	int currentStatus = STATUS_INITIAL;
	int offset = 0;
	char currentChar = *(text + offset);
	int finish = 0;
	
	memset(token, 0, sizeof(TOKEN));
	
	while(!finish) {
		currentChar = *(text + offset);
		
		switch(currentStatus) {
			case STATUS_INITIAL:
				if(currentChar > 0x29 && currentChar < 0x40) currentStatus = STATUS_READ_DIGIT;
				else if(currentChar == '-') currentStatus = STATUS_READ_DIGIT;
				else if(currentChar == 't') currentStatus = STATUS_READ_T;
				else if(currentChar == 'f') currentStatus = STATUS_READ_F;
				else currentStatus = STATUS_ERROR;
				break;
			
			case STATUS_READ_DIGIT:
				if(currentChar > 0x29 && currentChar < 0x40) currentStatus = STATUS_READ_DIGIT;
				else if(currentChar == 0x00) {
					currentStatus = STATUS_GIVE_TOKEN;
					token->type = TOKEN_INTEGER;
				}
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_T:
				if(currentChar == 'r') currentStatus = STATUS_READ_R;
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_R:
				if(currentChar == 'u') currentStatus = STATUS_READ_U;
				else currentStatus = STATUS_ERROR;
				break;
			
			case STATUS_READ_U:
				if(currentChar == 'e') currentStatus = STATUS_READ_E;
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_E:
				if(currentChar == 0x00) {
					currentStatus = STATUS_GIVE_TOKEN;
					token->type = TOKEN_BOOLEAN;
				}
				else currentStatus = STATUS_ERROR;
				break;
			
			case STATUS_READ_F:
				if(currentChar == 'a') currentStatus = STATUS_READ_A;
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_A:
				if(currentChar == 'l') currentStatus = STATUS_READ_L;
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_L:
				if(currentChar == 's') currentStatus = STATUS_READ_S;
				else currentStatus = STATUS_ERROR;
				break;
				
			case STATUS_READ_S:
				if(currentChar == 'e') currentStatus = STATUS_READ_E;
				else currentStatus = STATUS_ERROR;
				break;
					
			case STATUS_GIVE_TOKEN:
				finish = 1;
				break;
				
			case STATUS_ERROR:
				finish = 1;
				printf("Found error in the input text\n");
				break;
		}
		
		offset++;
	}
	
	return token;
}
