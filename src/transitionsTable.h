#ifndef TRANSITIONS_TABLE_H
#define TRANSITIONS_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_INTEGER 1
#define TOKEN_BOOLEAN 2
#define TOKEN_STRING 3

#define NUMBER_CHARS 256
#define NUMBER_STATUS 50

#define STATUS_RETURNING 0
#define STATUS_INITIAL 1
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
	TRANSITION *transitions;
  int maxStateAlloc;
  int offset;
	int takenStatusNo;
} TRANS_TABLE;

TRANS_TABLE *newTransitionsTable();
void deleteTransitionsTable(TRANS_TABLE *table);

void addTransitions(TRANS_TABLE *transTable);
void addFinalTransitions(TRANS_TABLE *table, int currentStatus, int tokenType);

void addNumbers(TRANS_TABLE *transTable);
void addStrings(TRANS_TABLE *transTable);
void addKeywords(TRANS_TABLE *transTable);

void addKeyword(TRANS_TABLE *transTable, char *keyword, int tokenType);

void addTransition(TRANS_TABLE *transTable,
				   int currentStatus,
				   char charRead,
				   int nextStatus,
				   functionTransition functionPointer);

void giveTokenBoolean(int *finish, TOKEN *token);
void giveTokenInt(int *finish, TOKEN *token);
void giveTokenError(int *finish, TOKEN *token);
void giveTokenString(int *finish, TOKEN *token);

TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead);

#endif
