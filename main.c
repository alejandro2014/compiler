#include <stdio.h>
#include "test.h"
#include "token.h"

#define STATUS_INITIAL 0
#define STATUS_READ_DIGIT 1
#define STATUS_GIVE_TOKEN 2
#define STATUS_READ_T 3
#define STATUS_READ_R 4
#define STATUS_READ_U 5
#define STATUS_READ_E 6
#define STATUS_ERROR 7

int main(int argn, char *argv) {
	testCase();
	return 0;
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
				
			case STATUS_GIVE_TOKEN:
				finish = 1;
				break;
		}
		
		offset++;
	}
	
	return token;
}
