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

void test_lab_content( ) {
	test_removeAdjacentEqualLetters( );

	test_removeExtraSpaces( );
}