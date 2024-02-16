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