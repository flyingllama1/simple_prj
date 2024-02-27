#include "../include.h"

#include <string/include.h>

void assertString( const char *expected, char *got,
	char const *fileName, char const *funcName,
	int line ) {
	if ( strcmp_( expected, got ) ) {
		fprintf( stderr, "File %s\n", fileName );
		fprintf( stderr, "%s - failed on line %d\n", funcName, line );
		fprintf( stderr, "Expected: \"%s\"\n", expected );
		fprintf( stderr, "Got: \"%s\"\n\n", got );
	}
	else
		fprintf( stderr, "%s - OK\n", funcName );
}