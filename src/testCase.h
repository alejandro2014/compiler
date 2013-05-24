#ifndef TESTCASE_H
#define TESTCASE_H

#define INITTESTCASE(nameTestCase) void nameTestCase() { \
		printf(#nameTestCase "\n");

#define REGISTER(testCase) testCase();
	
#define TEST(condition) void condition() { \
		printf("\t" #condition " - ");
		
#define ENDTEST printf("OK\n"); }

#include <assert.h>

#endif
