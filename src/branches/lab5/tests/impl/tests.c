#include "../include.h"

#include <assert.h>

#include <string/include.h>

void test_nonSpaceContent( ) {
	const char *s1 = " Hello World! ";
	const char *s2 = " \t\n ";
	const char *s3 = "";

	assert( *findNonSpace( s1 ) == 'H' );
	assert( *findNonSpace( s2 ) == '\0' );
	assert( *findNonSpace( s3 ) == '\0' );
}

void test_reversedSpaceContent( ) {
	const char *s1 = "Hello World!\t";
	const char *s2 = "\t\n";
	const char *s3 = "";
	const char *s4 = "Hello World!";
	
	assert( *findNonSpaceReverse( &s1[ strlen_( s1 ) - 1 ], s1 ) == '!' );
	assert( *findNonSpaceReverse( &s2[ strlen_( s2 ) - 1 ], s2 ) == '\0' );
	assert( *findNonSpaceReverse( &s3[ strlen_( s3 ) - 1 ], s3 ) == '\0' );

	assert( *findSpaceReverse( &s1[ strlen_( s1 ) - 1 ], s1 ) == '\t' );
	assert( *findSpaceReverse( &s2[ strlen_( s2 ) - 1 ], s2 ) == '\n' );
	assert( *findSpaceReverse( &s3[ strlen_( s3 ) - 1 ], s3 ) == '\0' );
	assert( *findSpaceReverse( &s4[ strlen_( s4 ) - 1 ], s4 ) == ' ' );
}

void test_spaceContent( ) {
	test_nonSpaceContent( );

	test_reversedSpaceContent( );

	const char *s1 = "Hello World!";
	const char *s2 = "\t\n";
	const char *s3 = "";

	assert( *findSpace( s1 ) == ' ' );
	assert( *findSpace( s2 ) == '\t' );
	assert( *findSpace( s3 ) == '\0' );
}

void test_compareContent( ) {
	const char *s1 = "Hello World!";
	const char *s2 = "World!";
	const char *s3 = " ";
	const char *s4 = "Hello World!";

	assert( strcmp_( s1, s2 ) < 0 );
	assert( strcmp_( s1, s3 ) > 0 );
	assert( strcmp_( s1, s4 ) == 0 );
}

void test_copyContent( ) {
	char *src = "Hello World!";
	char dst[ 64u ];

	char *end = strcpy_( src, src + strlen_( src ), dst );
	assert( strcmp_( src, dst ) == 0 );
}

void test_copyIfContent( ) {
	char *src = "Hello World!";
	char dst[ 64u ];

	char *end = copyIf( src, src + strlen_( src ), dst, isalpha );
	assert( strcmp_( dst, "HelloWorld" ) == 0 );
}

void test_copyIfReverseContent( ) {
	char *src = "Hello World!";
	char dst[ 64u ];

	char *end = copyIfReverse( &src[ strlen_( src ) - 1u ], src, dst, isalpha );
	assert( strcmp_( dst, "dlroWolleH" ) == 0 );
}

void test_string_content( ) {
	test_spaceContent( );

	test_compareContent( );

	test_copyContent( );

	test_copyIfContent( );

	test_copyIfReverseContent( );
}