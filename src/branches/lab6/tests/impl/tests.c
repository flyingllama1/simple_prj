#include "../include.h"

#include <exceptions/include.h>

#include <string/include.h>

void test_removeExtraSpaces( ) {
	char *a = "   good  job  ";
	removeExtraSpaces( a );
	ASSERT_STRING( " good job ", a );

	char *b = "			g		o		d		";
	removeExtraSpaces( b );
	ASSERT_STRING( "	g	o	d	", b );
}

void test_removeAdjacentEqualLetters( ) {
	char *a = "aaaaabbbcc";
	removeAdjacentEqualLetters( a );
	ASSERT_STRING( "abc", a );

	char *b = "abababac";
	removeAdjacentEqualLetters( b );
	ASSERT_STRING( "abababac", b );

	char *c = "good job ";
	removeAdjacentEqualLetters( c );
	ASSERT_STRING( "god job ", c );
}

void test_wordDescriptor( ) {
	char *a = "a1b2c3";
	digitToEndLetterToStart( a );
	ASSERT_STRING( "abc123", a );
	digitToEndReversedLetterToStart( a );
	ASSERT_STRING( "abc321", a );
	digitToStartLetterToEnd( a );
	ASSERT_STRING( "321abc", a );
}
void test_lab_content( ) {
	test_removeAdjacentEqualLetters( );

	test_removeExtraSpaces( );

	test_wordDescriptor( );
}