#include "../include.h"

size_t strlen_( const char *begin ) {
	char *end = begin;
	while ( *end != '\0' )
		++end;

	return end - begin;
}

char *strfind( char *begin, char *end, char ch ) {
	while ( begin != end && *begin != ch )
		++begin;

	return begin;
}

char *findNonSpace( char *begin ) {
	while ( *begin != '\0' && isspace( *begin ) )
		++begin;

	return begin;
}

char *findSpace( char *begin ) {
	while ( *begin != '\0' && !isspace( *begin ) )
		++begin;

	return begin;
}

char *findNonSpaceReverse( char *rbegin, const char *rend ) {
	while ( rbegin >= rend && isspace( *rbegin ) )
		--rbegin;

	return rbegin;
}

char *findSpaceReverse( char *rbegin, const char *rend ) {
	while ( rbegin >= rend && !isspace( *rbegin ) )
		--rbegin;

	return rbegin;
}

int strcmp_( const char *lhs, const char *rhs ) {
	while ( *lhs != '\0' && *rhs != '\0' && *lhs == *rhs ) {
		*lhs++;
		*rhs++;
	}

	return *lhs - *rhs;
}