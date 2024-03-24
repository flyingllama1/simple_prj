#include <malloc.h>
#include <memory.h>
#include <ctype.h>

#define MAX_STRING_SIZE 100u
#define MAX_N_WORDS_IN_STRING 100u
#define MAX_WORD_SIZE 20u

typedef struct WordDescriptor {
	char *m_begin;
	char *m_end;
} WordDescriptor_t;

typedef struct BagOfWords {
	WordDescriptor_t	m_words[ MAX_N_WORDS_IN_STRING ];
	size_t				m_size;
} BagOfWords_t;

size_t strlen_( const char *begin );

char *strfind( char *begin, char *end, char ch );

char *findNonSpace( char *begin );

char *findSpace( char *begin );

char *findNonSpaceReverse( char *rbegin, const char *rend );

char *findSpaceReverse( char *rbegin, const char *rend );

int strcmp_( const char *lhs, const char *rhs );

char *strcpy_( const char *beginSource, const char *endSource, char *beginDestination );

char *strcpyz_( const char *beginSource, char *beginDestination, const size_t size );

char *copyIf( char *beginSource, const char *endSource, char *beginDestination, int ( *f )( int ) );

char *copyIfReverse( char *rbeginSource, const char *rendSource, char *beginDestination, int ( *f )( int ) );

void removeAdjacentEqualLetters( char *str );

void removeExtraSpaces( char *str );

int getWord( char *beginSearch, WordDescriptor_t *word );

int getWordReverse( char *rbegin, char *rend, WordDescriptor_t *word );

void digitToEnd( WordDescriptor_t word );

void digitToEndReversed( WordDescriptor_t word );

void digitToStart( WordDescriptor_t word );

//void digitToStartReversed( WordDescriptor_t word );

void digitToEndLetterToStart( char *str );

void digitToEndReversedLetterToStart( char *str );

void digitToStartLetterToEnd( char *str );

void replaceDigitsWithSpaces( char *str );

int areWordsEqual( WordDescriptor_t a, WordDescriptor_t b );

void replaceWordsInString( char *src, char *w1, char *w2 );

int areWordsOrdered( char *src );

void getBagOfWords( BagOfWords_t *bag, char *s );

int isWordPalindrome( char *begin, char *end );

size_t countPalindromeWords( char *str );

void joinWords( char *s1, char *s2, char *res );

void reverseWordsOrder( char *str );