#include "helper.h"
#include "transitionsTable.h"

char *getTokenName(int tokenNumber) {
	char *name = "";

	switch(tokenNumber) {
		case NO_TOKEN:           name = "NO TOKEN "; break;
		case TOKEN_INTEGER:      name = "Integer  "; break;
		case TOKEN_BOOLEAN:      name = "Boolean  "; break;
		case TOKEN_STRING:       name = "String   "; break;
		case TOKEN_CURLY_OPEN:   name = "Curly {  "; break;
		case TOKEN_CURLY_CLOSE:  name = "Curly }  "; break;
		case TOKEN_SQUARE_OPEN:  name = "Square [ "; break;
		case TOKEN_SQUARE_CLOSE: name = "Square ] "; break;
		case TOKEN_COLON:        name = "Colon ':'"; break;
		case TOKEN_COMMA:        name = "Comma ','"; break;
	}

	return name;
}

char *loadFile(char *path) {
	char *buffer;
	int fileSize;

	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	buffer = (char *) malloc(sizeof(char) * fileSize);
	fseek(file, 0, SEEK_SET);
	fread(buffer, 1, fileSize, file);
	fclose(file);

	return buffer;
}
