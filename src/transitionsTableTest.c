//#include "transitionsTableTest.h"

#include "testCase.h" //-
#include "parser.h"
#include "transitionsTable.h"

void transitionsTableTestCase();
void itShouldCreateTransitionsTable();
void itShouldInitializeTransitionsTable();
void itShouldAddAKeyWord();
void itShouldAddSeveralKeywords();
void transitionsTable_before();

INITTESTCASE(transitionsTableTestCase)
	REGISTER(itShouldCreateTransitionsTable)
	REGISTER(itShouldInitializeTransitionsTable)
	REGISTER(itShouldAddAKeyWord)
	REGISTER(itShouldAddSeveralKeywords)
}

extern TRANSITION transitionsTable[NUMBER_STATUS][NUMBER_CHARS];

TEST(itShouldCreateTransitionsTable)
	TRANS_TABLE *table = newTransitionsTable();

	assert(table != NULL);
	assert(table->transitions != NULL);

	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldInitializeTransitionsTable)
	TRANS_TABLE *table = newTransitionsTable();
	int nextStatus = getTransition(table, 2, 't')->nextStatus;
	printf("> Next status: %d\n", nextStatus);

	assert(nextStatus == STATUS_ERROR);
	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldAddAKeyWord)
	TRANS_TABLE *table = newTransitionsTable();
	char *booleanText = "false";
	TOKEN *token = NULL;

	addKeyword(table, booleanText, TOKEN_BOOLEAN);
	token = parse(table, booleanText);

	assert(token->type == TOKEN_BOOLEAN);

	free(token);
	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldAddSeveralKeywords)
	TRANS_TABLE *table = newTransitionsTable();
	char *booleanText = "false";
	char *intText = "1234";
	TOKEN *token = NULL;

	addKeyword(table, booleanText, TOKEN_BOOLEAN);
	addKeyword(table, intText, TOKEN_INTEGER);

	token = parse(table, booleanText);
	assert(token->type == TOKEN_BOOLEAN);
	free(token);

	token = parse(table, intText);
	assert(token->type == TOKEN_INTEGER);

	free(token);
	deleteTransitionsTable(table);
ENDTEST

void transitionsTable_before() {
	//initializeTransitionsTable();
}
