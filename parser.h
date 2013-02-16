#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_INTEGER 1
#define TOKEN_BOOLEAN 2

#define NUMBER_CHARS 256
#define NUMBER_STATUS 8

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
#define STATUS_ERROR 11

typedef void (*functionTransition)(void);

typedef struct {
	int nextStatus;
	functionTransition function;
} TRANSITION;

typedef struct {
	char type;
} TOKEN;

TOKEN *parse(char *text);
void initializeTransitionsTable();

#endif
