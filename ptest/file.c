//@TestCase transitionsTableTestCase

TEST(itShouldCreateTransitionsTable)
	TRANS_TABLE *table = newTransitionsTable();
	
	assert(table != NULL);
	assert(table->transitions != NULL);
	
	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldDeleteTransitionsTable)
	/*TRANS_TABLE *table = newTransitionsTable();
	
	deleteTransitionsTable(table);
	
	assert(table == NULL);*/
ENDTEST

TEST(itShouldInitializeTransitionsTable)
	TRANS_TABLE *table = newTransitionsTable();
	
	assert(table->transitions[2]['t'].nextStatus == STATUS_ERROR);
	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldAddAKeyWord)
	TRANS_TABLE *table = newTransitionsTable();
	unsigned char *booleanText = "false";
	TOKEN *token = NULL;
	
	addKeyword(table, booleanText, TOKEN_BOOLEAN);
	token = parse(table, booleanText);
	
	assert(token->type == TOKEN_BOOLEAN);
	
	free(token);
	deleteTransitionsTable(table);
ENDTEST

TEST(itShouldAddSeveralKeywords)
	TRANS_TABLE *table = newTransitionsTable();
	unsigned char *booleanText = "false";
	unsigned char *intText = "1234";
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
