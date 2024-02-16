#include <malloc.h>
#include <memory.h>
#include <ctype.h>

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