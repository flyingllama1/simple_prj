#include "../include.h"

#include <stdio.h>

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

int isWordPalindrome( char *begin, char *end ) {
	--end; // avoid '\0' char.

	while ( end > begin ) {
		if ( *begin != *end )
			return 0;

		++begin;
		--end;
	}

	return 1;
}

size_t countPalindromeWords( char *str ) {
	char *begin = findNonSpace( str );
	char *end = str + strlen_( str );
	char *li = strfind( begin, end, ',' );

	int is_final_word = *li == '\0' && end > begin;

	size_t ret = 0u;
	while ( *li != '\0'
		|| is_final_word ) {
		ret += isWordPalindrome( begin, li );
		if ( is_final_word )
			break;

		if ( end <= begin )
			break;

		begin = findNonSpace( li + 1 );
		li = strfind( begin, end, ',' );
		is_final_word = *li == '\0' && end > begin;
	}

	return ret;
}

void joinWords( char *s1, char *s2, char *res ) {
	WordDescriptor_t w1, w2;

	int f1, f2;
	while ( ( f1 = getWord( s1, &w1 ),
		f2 = getWord( s2, &w2 ) ),
		f1 ) {
		if ( f1 ) {
			for ( char *c = w1.m_begin; c != w1.m_end; ++c ) {
				*res++ = *c;
			}

			s1 = w1.m_end;
			f1 = getWord( s1, &w1 );

			if ( f1 || f2 )
				*res++ = ' ';
		}
		if ( f2 ) {
			for ( char *c = w2.m_begin; c != w2.m_end; ++c ) {
				*res++ = *c;
			}

			s2 = w2.m_end;
			f2 = getWord( s2, &w2 );

			if ( f1 || f2 )
				*res++ = ' ';
		}
	}

	*res = '\0';
}

void reverseWordsOrder( char *str ) {
	char dst[ MAX_STRING_SIZE ];
	char *begin = str + strlen_( str );
	char *end = str;

	BagOfWords_t bag;
	getBagOfWords( &bag, str );

	size_t j = 0u;
	for ( int i = bag.m_size - 1u; i != -1; --i ) {
		for ( char *c = bag.m_words[ i ].m_begin; c != bag.m_words[ i ].m_end; ++c )
			dst[ j++ ] = *c;

		if ( i != 0 )
			dst[ j++ ] = ' ';
	}

	dst[ j++ ] = '\0';
	strcpy_( dst, dst + j, str );
}

int isWordContainsChar( WordDescriptor_t word, char ch ) {
	for ( char *c = word.m_begin; c != word.m_end; ++c )
		if ( *c == ch )
			return 1;

	return 0;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA_Status( char *str ) {
	if ( *str == '\0' )
		return EMPTY_STRING;

	char *begin = str;

	WordDescriptor_t word, track = { NULL };
	while ( getWord( str, &word ) ) {
		if ( isWordContainsChar( word, 'A' )
			|| isWordContainsChar( word, 'a' ) ) {
			if ( track.m_begin == NULL )
				return FIRST_WORD_WITH_A;
			else
				return WORD_FOUND;
		}

		track = word;
		str = word.m_end;
	}

	return NOT_FOUND_A_WORD_WITH_A;
}

void printWordBeforeFirstWordWithA( char *str ) {
	if ( *str == '\0' )
		return;

	char *begin = str;

	WordDescriptor_t word, track = { NULL };
	while ( getWord( str, &word ) ) {
		if ( isWordContainsChar( word, 'A' )
			|| isWordContainsChar( word, 'a' ) ) {
			if ( track.m_begin == NULL )
				for ( char *c = word.m_begin; c != word.m_end; ++c )
					printf( "%c", *c );
			else
				for ( char *c = track.m_begin; c != track.m_end; ++c )
					printf( "%c", *c );
			printf( "\n" );
		}

		track = word;	
		str = word.m_end;
	}
}

void getWordData( WordDescriptor_t word, char *dst ) {
	for ( char *c = word.m_begin; c != word.m_end; ++c )
		*dst++ = *c;

	*dst = '\0';
}

int isWordInBagOfWords( WordDescriptor_t word, BagOfWords_t bag ) {
	char wdata[ MAX_STRING_SIZE ],
		_data[ MAX_STRING_SIZE ];
	getWordData( word, wdata );
	for ( size_t i = 0; i < bag.m_size; ++i ) {
		getWordData( bag.m_words[ i ], _data );
		if ( strcmp_( wdata, _data ) == 0 )
			return 1;
	}

	return 0;
}

char *lastWordInFirstStringInSecondString( char *s1, char *s2 ) {
	BagOfWords_t b1, b2;
	getBagOfWords( &b1, s1 );
	getBagOfWords( &b2, s2 );

	char ret[ MAX_STRING_SIZE ];
	for ( int i = b1.m_size - 1u; i != -1; --i ) {
		for ( int j = 0; j < b2.m_size; ++j ) {
			if ( isWordInBagOfWords( b1.m_words[ i ], b2 ) ) {
				getWordData( b1.m_words[ i ], ret );
				return ret;
			}
		}
	}

	return "";
}

int hasSameWords( char *str ) {
	BagOfWords_t bag;
	getBagOfWords( &bag, str );

	for ( size_t i = 0u; i < bag.m_size; ++i )
		for ( size_t j = i + 1u; j < bag.m_size; ++j )
			if ( areWordsEqual( bag.m_words[ i ], bag.m_words[ j ] ) )
				return 1;

	return 0;
}

int hasSimilarAlphabet( char *s1, char *s2 ) {
	int a1[ 26u ] = { 0 };
	int a2[ 26u ] = { 0 };

	for ( size_t i = 0u; i < strlen_( s1 ); ++i )
		a1[ s1[ i ] - 'a' ] = 1;

	for ( size_t i = 0u; i < strlen_( s2 ); ++i )
		a2[ s2[ i ] - 'a' ] = 1;

	for ( size_t i = 0u; i < 26u; ++i )
		if ( a1[ i ] != a2[ i ] )
			return 0;

	return 1;
}

int hasWordsWithSimilarAlphabet( char *str ) {
	BagOfWords_t bag;
	getBagOfWords( &bag, str );

	for ( size_t i = 0u; i < bag.m_size; ++i ) {
		for ( size_t j = i + 1u; j < bag.m_size; ++j ) {
			char w1[ MAX_STRING_SIZE ], w2[ MAX_STRING_SIZE ];
			getWordData( bag.m_words[ i ], w1 );
			getWordData( bag.m_words[ j ], w2 );

			if ( hasSimilarAlphabet( w1, w2 ) )
				return 1;
		}
	}

	return 0;
}

void getStringWithoutWordsSimilarLastWord( char *str ) {
	char dst[ MAX_STRING_SIZE ];
	size_t len = 0u;

	BagOfWords_t bag;
	getBagOfWords( &bag, str );
	if ( !bag.m_size )
		return;

	WordDescriptor_t comp = bag.m_words[ bag.m_size - 1u ];
	for ( size_t i = 0u; i < bag.m_size - 1u; ++i ) {
		if ( !areWordsEqual( bag.m_words[ i ], comp ) ) {
			for ( char *c = bag.m_words[ i ].m_begin; c != bag.m_words[ i ].m_end; ++c ) {
				dst[ len++ ] = *c;
			}

			dst[ len++ ] = ' ';
		}
	}

	dst[ len-- ] = '\0';

	strcpy_( dst, dst + len, str );
}