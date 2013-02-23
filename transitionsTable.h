#ifndef TRANSITIONS_TABLE_H
#define TRANSITIONS_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_INTEGER 1
#define TOKEN_BOOLEAN 2
#define TOKEN_STRING 3

#define NUMBER_CHARS 256
#define NUMBER_STATUS 13

#define STATUS_INITIAL 0
#define STATUS_READ_DIGIT 1
#define STATUS_GIVE_TOKEN 2
#define STATUS_READ_A 3
#define STATUS_READ_E 4
#define STATUS_READ_F 5
#define STATUS_READ_L 6
#define STATUS_READ_R 7
#define STATUS_READ_S 8
#define STATUS_READ_T 9
#define STATUS_READ_U 10
#define STATUS_READ_STRING 11

#define STATUS_ERROR 100

typedef struct {
	char type;
} TOKEN;

typedef void (*functionTransition)(int*, TOKEN*);

typedef struct {
	int nextStatus;
	functionTransition function;
} TRANSITION;

typedef struct {
	int numberOfStatus;
	int numberOfChars;
	TRANSITION **transitions;
} TRANS_TABLE;

TRANS_TABLE *newTransitionsTable();
void deleteTransitionsTable(TRANS_TABLE *table);

void addTransitions(TRANS_TABLE *transTable);

void addKeyword(TRANS_TABLE *transTable, unsigned char *keyword, int tokenType);

void addTransition(TRANS_TABLE *transTable,
				   int currentStatus,
				   unsigned char charRead,
				   int nextStatus,
				   functionTransition functionPointer);

void giveTokenBoolean(int *finish, TOKEN *token);
void giveTokenInt(int *finish, TOKEN *token);
void giveTokenError(int *finish, TOKEN *token);
void giveTokenString(int *finish, TOKEN *token);

#endif
