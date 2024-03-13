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

size_t strlen_( const char *begin );

char *strfind( char *begin, char *end, char ch );

char *findNonSpace( char *begin );

char *findSpace( char *begin );

char *findNonSpaceReverse( char *rbegin, const char *rend );

char *findSpaceReverse( char *rbegin, const char *rend );

int strcmp_( const char *lhs, const char *rhs );

char *strcpy_( const char *beginSource, const char *endSource, char *beginDestination );

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