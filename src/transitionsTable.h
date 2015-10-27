#ifndef TRANSITIONS_TABLE_H
#define TRANSITIONS_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_TOKEN 0
#define TOKEN_INTEGER 1
#define TOKEN_BOOLEAN 2
#define TOKEN_STRING 3
#define TOKEN_CURLY_OPEN 4
#define TOKEN_CURLY_CLOSE 5
#define TOKEN_SQUARE_OPEN 6
#define TOKEN_SQUARE_CLOSE 7
#define TOKEN_COLON 8
#define TOKEN_COMMA 9

#define NUMBER_CHARS 256
#define NUMBER_STATUS 50

#define STATUS_RETURNING 0
#define STATUS_INITIAL 1
#define STATUS_ERROR 100

typedef struct {
	char type;
	char *content;
} TOKEN;

typedef struct {
	int nextStatus;
	int tokenReturned;
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
void addTransition(TRANS_TABLE *transTable, int currentStatus, char charRead, int nextStatus, int tokenReturned);
TRANSITION *getTransition(TRANS_TABLE *transTable, int currentStatus, char charRead);

void addNumbers(TRANS_TABLE *transTable);
void addStrings(TRANS_TABLE *transTable);

void addKeywords(TRANS_TABLE *transTable);
void addKeyword(TRANS_TABLE *transTable, char *keyword, int tokenType);

void addSpecialChars(TRANS_TABLE *table);
void addSpecialChar(TRANS_TABLE *table, char character, int tokenType);

#endif
