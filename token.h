#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_INTEGER 1
#define TOKEN_BOOLEAN 2

typedef struct {
	char type;
} TOKEN;

TOKEN *parse(char *text);

#endif
