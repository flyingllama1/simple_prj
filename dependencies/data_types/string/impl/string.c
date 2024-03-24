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

char *strcpy_( const char *beginSource, const char *endSource, char *beginDestination ) {
	size_t size = endSource - beginSource;

	memcpy( beginDestination, beginSource, size );
	*( beginDestination + size ) = '\0';

	return beginDestination + size;
}

char *copyIf( char *beginSource, const char *endSource, char *beginDestination, int ( *f )( int ) ) {
	while ( beginSource != endSource ) {
		if ( f( *beginSource ) ) {
			*beginDestination = *beginSource;
			++beginDestination;
		}

		++beginSource;
	}

	*beginDestination = '\0';

	return beginDestination;
}

char *copyIfReverse( char *rbeginSource, const char *rendSource, char *beginDestination, int ( *f )( int ) ) {
	char *rbegin_dst = beginDestination;
	while ( *rbeginSource >= -1 && *rbeginSource <= 255 && rbeginSource >= rendSource ) {
		if ( f( *rbeginSource ) ) {
			*rbegin_dst = *rbeginSource;
			++rbegin_dst;
		}

		--rbeginSource;
	}

	*rbegin_dst = '\0';

	return rbegin_dst;
}

void removeAdjacentEqualLetters( char *str ) {
	if ( *str != '\0' ) {
		str++;
	}

	char *readbuf = str;
	while ( *readbuf != '\0' ) {
		if ( *readbuf != *( --str ) )
			*( ++str ) = *readbuf;

		++str;
		++readbuf;
	}

	*str = '\0';
}

void removeExtraSpaces( char *str ) {
	char *readbuf = str;
	while ( *readbuf != '\0' ) {
		if ( isspace( *readbuf ) ) {
			char *wbuf = str;
			if ( !isspace( *( wbuf-- ) ) ) {
				*( ++str ) = *readbuf;
			}
		}
		else
			*( ++str ) = *readbuf;

		++readbuf;
	}

	*( ++str ) = '\0';
}

int getWord( char *beginSearch, WordDescriptor_t *word ) {
	word->m_begin = findNonSpace( beginSearch );
	if ( *word->m_begin == '\0' )
		return 0;

	word->m_end = findSpace( word->m_begin );

	return 1;
}

void digitToEnd( WordDescriptor_t word ) {
	char _stringBuffer[ MAX_STRING_SIZE + 1 ];
	char *endStringBuffer = strcpy_( word.m_begin, word.m_end,
		_stringBuffer );

	char *recPosition = copyIf( _stringBuffer, endStringBuffer, word.m_begin, isalpha );
	copyIf( _stringBuffer, endStringBuffer, recPosition, isdigit );
}

void digitToEndReversed( WordDescriptor_t word ) {
	char _stringBuffer[ MAX_STRING_SIZE + 1 ];
	char *endStringBuffer = strcpy_( word.m_begin, word.m_end,
		_stringBuffer );

	char *recPosition = copyIf( _stringBuffer, endStringBuffer, word.m_begin, isalpha );
	copyIfReverse( endStringBuffer, _stringBuffer, recPosition, isdigit );
}

void digitToStart( WordDescriptor_t word ) {
	char _stringBuffer[ MAX_STRING_SIZE + 1 ];
	char *endStringBuffer = strcpy_( word.m_begin, word.m_end,
		_stringBuffer );

	char *recPosition = copyIf( _stringBuffer, endStringBuffer, word.m_begin, isdigit );
	copyIf( _stringBuffer, endStringBuffer, recPosition, isalpha );
}

void digitToEndLetterToStart( char *str ) { // 3(1)
	WordDescriptor_t word;

	char *readbuf = str;
	while ( getWord( readbuf, &word ) ) {
		digitToEnd( word );
		readbuf = word.m_end;
	}
}

void digitToEndReversedLetterToStart( char *str ) { // 3(2)
	WordDescriptor_t word;

	char *readbuf = str;
	while ( getWord( readbuf, &word ) ) {
		digitToEndReversed( word );
		readbuf = word.m_end;
	}
}

void digitToStartLetterToEnd( char *str ) { // 3(3)
	WordDescriptor_t word;
	
	char *readbuf = str;
	while ( getWord( readbuf, &word ) ) {
		digitToStart( word );
		readbuf = word.m_end;
	}
}

void replaceDigitsWithSpaces( char *str ) {
	char _stringBuffer[ MAX_STRING_SIZE + 1 ];
	char *end = str + strlen_( str );
	char *readbuf = _stringBuffer;
	char *endbuf = strcpy_( str, end, readbuf );

	while ( *readbuf != '\0' ) {
		if ( isalpha( *readbuf ) )
			*str++ = *readbuf;
		else {
			// 2 -> 210 -> 21 skip zero.
			while ( isdigit( *readbuf ) 
				&& *readbuf != '0' ) {
				*str++ = ' ';
				( *readbuf )--;
			}
		}
		
		++readbuf;
	}

	*str = '\0';
}

int areWordsEqual( WordDescriptor_t a, WordDescriptor_t b ) {
	char *rb1 = a.m_begin;
	char *rb2 = b.m_begin;

	while ( ( *rb1 != ' ' || *rb2 != ' ' )
		&& ( *rb1 != '\0' && *rb2 != '\0' ) ) {
		if ( *rb1 != *rb2
			&& ( *rb1 != '\0' && *rb2 != '\0' ) )
			return 0;

		++rb1;
		++rb2;
	}

	return rb1 == a.m_end && rb2 == b.m_end;
}

void replaceWordsInString( char *src, char *w1, char *w2 ) {
	size_t s1 = strlen_( w1 );
	size_t s2 = strlen_( w2 );

	WordDescriptor_t wo1 = { w1, w1 + s1 };
	WordDescriptor_t wo2 = { w2, w2 + s2 };

	WordDescriptor_t word;

	char *readbuf = src;
	char *recbuf = src;

	char buf[ MAX_STRING_SIZE ];
	if ( s2 > s1 ) {
		strcpy_( src, src + strlen_( src ), buf );
		readbuf = buf;
		recbuf = src;
	}

	while ( getWord( readbuf, &word ) ) {
		WordDescriptor_t res = wo2;
		if ( !areWordsEqual( word, wo1 ) )
			res = word;

		for ( char *c = res.m_begin; c != res.m_end; ++c ) {
			*recbuf++ = *c;
		}
		
		*recbuf++ = ' ';

		readbuf = word.m_end;
	}

	*( recbuf - 1u ) = '\0';
}

int areWordsOrdered( char *src ) {
	WordDescriptor_t a, b;
	if ( getWord( src, &a ) ) {
		b = a;
		src = a.m_end;
		while ( getWord( src, &a ) ) {
			if ( !areWordsEqual( a, b ) )
				return 0;

			b = a;
			src = a.m_end;
		}

		return 1;
	}
	else {
		return 1;
	}
}

void getBagOfWords( BagOfWords_t *bag, char *s ) {
	WordDescriptor_t word;

	bag->m_size = 0u;
	while ( getWord( s, &word ) ) {
		bag->m_words[ bag->m_size ] = word;
		++bag->m_size;

		s = word.m_end;
	}
}