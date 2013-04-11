#ifndef TEST_H
#define TEST_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

void parserTestCase();
void IShouldIdentifyAPositiveInt();
void IShouldIdentifyANegativeInt();
void ItShouldIdentifyABooleanTrue();
void ItShouldIdentifyABooleanFalse();
void itShouldIdentifyAString();
void itShouldIdentifyTokensSeparatedBySpace();
#endif

