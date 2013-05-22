#ifndef TRANSITIONS_TABLE_TEST_H
#define TRANSITIONS_TABLE_TEST_H

#include <assert.h>
#include "parser.h"
#include "transitionsTable.h"

void transitionsTablETestCase();

void itShouldCreateTransitionsTable();
void itShouldDeleteTransitionsTable();
void itShouldInitializeTransitionsTable();
void itShouldAddAKeyWord();
void itShouldAddSeveralKeywords();
void transitionsTable_before();

#endif

