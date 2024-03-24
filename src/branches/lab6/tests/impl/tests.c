#include "../include.h"

#include <assert.h>

#include <exceptions/include.h>

#include <string/include.h>

BagOfWords_t _bag1;
BagOfWords_t _bag2;

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

void test_replaceDigitsWithSpaces( ) {
	char *t = "a2b";
	replaceDigitsWithSpaces( t );
	ASSERT_STRING( "a  b", t );

	char *s = "a10b";
	replaceDigitsWithSpaces( s );
	ASSERT_STRING( "a b", s );
}

void test_replaceWordsInString( ) {
	char *a = "aaa bless";
	replaceWordsInString( a, "aaa", "dog" );
	ASSERT_STRING( "dog bless", a );

	char *b = "aaaaaa drain makes aaaaaa powerful";
	replaceWordsInString( b, "aaaaaa", "monki" );
	ASSERT_STRING( "monki drain makes monki powerful", b );

	char *c = "Z likes bananas";
	replaceWordsInString( c, "Z", "monki" );
	ASSERT_STRING( "monki likes bananas", c );
}

void test_areWordsOrdered( ) {
	char *a = "walter white";
	int za = areWordsOrdered( a );
	assert( za == 0 );

	char *b = "w w";
	int zb = areWordsOrdered( b );
	assert( zb == 1 );
}

void test_countPalindromeWords( ) {
	char *a = "333, sf";
	size_t za = countPalindromeWords( a );
	assert( za == 1u );

	char *b = "";
	size_t zb = countPalindromeWords( b );
	assert( zb == 0u );

	char *c = " fuuuuf, drg, eeeeee";
	size_t zc = countPalindromeWords( c );
	assert( zc == 2u );
}

void test_joinWords( ) {
	char a[ MAX_STRING_SIZE ];
	joinWords( "monki like", "just bananas", a );
	ASSERT_STRING( "monki just like bananas", a );

	char b[ MAX_STRING_SIZE ];
	joinWords( "amazing flip", "monki", b );
	ASSERT_STRING( "amazing monki flip", b );

	char c[ MAX_STRING_SIZE ];
	joinWords( "monki chase my money", "bot", c );
	ASSERT_STRING( "monki bot chase my money", c );
}

void test_reverseWordsOrder( ) {
	char *a = "monki dont lie";
	reverseWordsOrder( a );
	ASSERT_STRING( "lie dont monki", a );

	char *b = "";
	reverseWordsOrder( b );
	ASSERT_STRING( "", b );

	char *c = "monkiflip";
	reverseWordsOrder( c );
	ASSERT_STRING( "monkiflip", c );
}

void test_getWordBeforeFirstWordWithA_Status( ) {
	char *a = "";
	assert( getWordBeforeFirstWordWithA_Status( a ) == EMPTY_STRING );
	
	char *b = "a monki";
	assert( getWordBeforeFirstWordWithA_Status( b ) == FIRST_WORD_WITH_A );

	char *c = "monke hate drugs";
	assert( getWordBeforeFirstWordWithA_Status( c ) == WORD_FOUND );

	char *d = "monki trust you";
	assert( getWordBeforeFirstWordWithA_Status( d ) == NOT_FOUND_A_WORD_WITH_A );
}

void test_lastWordInFirstStringInSecondString( ) {
	ASSERT_STRING( "D", lastWordInFirstStringInSecondString( "A B C D", "C D E F" ) );
	ASSERT_STRING( "C", lastWordInFirstStringInSecondString( "A B C D", "C G E F" ) );
	ASSERT_STRING( "", lastWordInFirstStringInSecondString( "A B C D", "E F G H" ) );
}

void test_hasSameWords( ) {
	assert( hasSameWords( "a a b" ) );
	assert( !hasSameWords( "a c b" ) );

	assert( !hasSameWords( "" ) );
	assert( !hasSameWords( "a" ) );
}

void test_lab_content( ) {
	test_removeAdjacentEqualLetters( );

	test_removeExtraSpaces( );

	test_wordDescriptor( );

	test_replaceDigitsWithSpaces( );

	test_replaceWordsInString( );

	test_areWordsOrdered( );

	test_countPalindromeWords( );

	test_joinWords( );

	test_reverseWordsOrder( );

	test_getWordBeforeFirstWordWithA_Status( );

	test_lastWordInFirstStringInSecondString( );

	test_hasSameWords( );
}