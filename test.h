#ifndef TEST_H
#define TEST_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_INTEGER 1

typedef struct {
	char type;
} TOKEN;

void testCase();
void testOne();
void testTwo();
TOKEN *parse(char *text);
#endif

