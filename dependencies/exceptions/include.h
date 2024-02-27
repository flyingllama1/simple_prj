#include <stdio.h>
#include <stdlib.h>

#define ERR_GET_FN_NAME(fn) (#fn)

#define STD_ERROR(fn, err) \
	fprintf(stderr, "0x%p: %s -> %s.\n", &fn, ERR_GET_FN_NAME(fn), err)

#define STD_ERROR_N_EXIT(fn, err) \
	fprintf(stderr, "0x%p: %s -> %s.\n", &fn, ERR_GET_FN_NAME(fn), err); \
	exit(1);

#define ASSERT_STRING(expected, got) assertString(expected, got, \
	__FILE__, __FUNCTION__, __LINE__ )

void assertString( const char *expected, char *got,
	char const *fileName, char const *funcName,
	int line );