#include "../include.h"

#include "../../tests/include.h"

#include <exceptions/include.h>

#include <vdvector/include.h>

#include <matrix/include.h>

#include <file_manager/include.h>

#include <string/include.h>

#include <math.h>

void task01( vdvector_t *ms ) {
	FILE *file = fopen( "data/task01.txt", "r" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task01, "cannot open file task01.txt" );

	int n;
	while ( fscanf( file, "%d", &n  ) == 1 ) {
		int *arr = ( int * )malloc( sizeof( int ) * n * n );
		for ( size_t i = 0u; i < n * n; ++i )
			fscanf( file, "%d", &arr[ i ] );

		matrix_t mx = createMatrixFromArray( arr, n, n );
		transposeSquareMatrix( &mx );

		vdvector_pushBack( ms, &mx );
	}

	gWriteMatrix( "data/task01.txt", *ms );

	fclose( file );
}

void task02( vdvector_t *v ) {
	FILE *file = fopen( "data/task02.txt", "r" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task02, "cannot open file task02.txt" );

	float f;
	while ( fscanf( file, "%f", &f ) == 1 )
		vdvector_pushBack( v, &f );

	gWriteFloat( "data/task02.txt", *v, "%.2f " );

	fclose( file );
}

void doOperation( int *c, int a, int b, char op ) {
	switch ( op ) {
	case '+': *c = a + b; break;
	case '-': *c = a - b; break;
	case '*': *c = a * b; break;
	case '/': *c = a / b; break;
	}
}

int isValidOperator( char c ) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void task03( int *v ) {
	FILE *file = fopen( "data/task03.txt", "r" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task03, "cannot open file task03.txt" );

	int  a, b, c;
	char operation1, operation2;

	fscanf( file, "%d %c %d %c %d", &a, &operation1, &b, &operation2, &c );
	int had_one_more_operation = isValidOperator( operation2 );

	int ret;
	if ( had_one_more_operation ) {
		if ( operation1 != '*' && operation1 != '/' ) {
			if ( operation2 == '*' || operation2 == '/' ) {
				doOperation( &ret, b, c, operation2 );
				doOperation( &ret, a, ret, operation1 );
			}
			else {
				doOperation( &ret, a, b, operation1 );
				doOperation( &ret, ret, c, operation2 );
			}
		}
		else {
			doOperation( &ret, a, b, operation1 );
			doOperation( &ret, ret, c, operation2 );
		}
	}
	else {
		doOperation( &ret, a, b, operation1 );
	}

	fclose( file );

	FILE *write = fopen( "data/task03.txt", "w" );
	if ( write == NULL )
		STD_ERROR_N_EXIT( task03, "cannot open file task03.txt" );

	fprintf( write, "%d %c %d ", a, operation1, b );
	if ( had_one_more_operation )
		fprintf( write, "%c %d ", operation2, c );

	fprintf( write, "= %d", ret );

	fclose( write );

	*v = ret;
}

void task06( float x, vdvector_t *v ) {
	FILE *file = fopen( "data/task06.bin", "rb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task06, "cant open file task06.bin" );

	polynomial_t poly;
	while ( fread( &poly, sizeof( polynomial_t ), 1, file ) == 1 ) {
		int res = poly.m_coeff;
		for ( size_t i = 1u; i < poly.m_power; ++i )
			res += poly.m_coeff * pow( x, i );

		if ( res != 0 )
			vdvector_pushBack( v, &poly );
	}
	fclose( file );

	FILE *rd = fopen( "data/task06.bin", "wb" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task06, "cannot open file task06.bin" );

	for ( size_t i = 0u; i < v->m_size; ++i ) {
		polynomial_t p;
		vdvector_get( v, i, &p );

		fwrite( &p, sizeof( polynomial_t ), 1u, rd );
	}

	fclose( rd );
}

void task07( vdvector_t *nums ) {
	FILE *file = fopen( "data/task07.bin", "rb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task07, "cant open file task07.bin" );
	
	vdvector_t pos = vdvector_create( 0u, sizeof( int ) );
	vdvector_t neg = vdvector_create( 0u, sizeof( int ) );

	int n;
	while ( fread( &n, sizeof( int ), 1, file ) == 1 ) {
		if ( n >= 0 )
			vdvector_pushBack( &pos, &n );
		else
			vdvector_pushBack( &neg, &n );
	}

	fclose( file );

	FILE *rd = fopen( "data/task07.bin", "wb" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task07, "cant open file task07.bin" );

	for ( size_t i = 0u; i < pos.m_size; ++i ) {
		vdvector_get( &pos, i, &n );

		fwrite( &n, sizeof( int ), 1u, rd );
		vdvector_pushBack( nums, &n );
	}

	for ( size_t i = 0u; i < neg.m_size; ++i ) {
		vdvector_get( &neg, i, &n );

		fwrite( &n, sizeof( int ), 1u, rd );
		vdvector_pushBack( nums, &n );
	}

	fclose( rd );
}

int isContainsStringSequence( char *str, char *sq ) {
	int sq_len = strlen_( sq );
	int sq_it = 0;

	while ( *str != '\0' ) {
		if ( *str == sq[ sq_it ] )
			++sq_it;
		else
			sq_it = 0;

		if ( sq_it == sq_len )
			return 1;

		++str;
	}

	return 0;
}

void task04( char *alphabet ) {
	FILE *file = fopen( "data/task04.txt", "r" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task04, "cant open file task04.txt" );

	vdvector_t words = vdvector_create( 0u, sizeof( char* ) );
	
	char rbuf[ MAX_STRING_SIZE ];
	while ( fscanf( file, "%s", &rbuf ) == 1 ) {
		if ( isContainsStringSequence( rbuf, alphabet ) )
			vdvector_pushBack( &words, rbuf );
	}
	fclose( file );

	FILE *rd = fopen( "data/task04.txt", "w" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task09, "cannot open file task04.txt" );

	for ( size_t i = 0u; i < words.m_size; ++i ) {
		vdvector_get( &words, i, &rbuf );

		fprintf( rd, "%s ", rbuf );
	}

	fclose( rd );
}

int isStringContainsNewLine( char *s ) {
	int contains = 0;
	while ( *s != '\0' && *s != '\n' ) {
		if ( *s == '\n' ) {
			contains = 1;
			break;
		}

		++s;
	}

	return contains;
}

void task05( vdvector_t *s ) {
	FILE *file = fopen( "data/task05.txt", "r" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task05, "cant open file task05.txt" );

	vdvector_t words = vdvector_create( 0u, sizeof( char * ) );

	char good_word[ MAX_STRING_SIZE ];
	char rbuf[ MAX_STRING_SIZE ];

	int max_len = -1;
	while ( fgets( rbuf, 100, file ) != NULL ) {
		int len = 0;
		char word[ MAX_STRING_SIZE ];
		char good_word[ MAX_STRING_SIZE ];
		for ( size_t i = 0u; i < strlen_( rbuf ) && rbuf[ i ] != '\0'; ++i ) {
			if ( isspace( rbuf[ i ] ) ) {
				if ( len > max_len ) {
					max_len = len;
					word[ len ] = '\0';
					memcpy( &good_word, &word, sizeof( char ) * ( len + 1 ) ); // include zero symbol.
				}

				len = 0;

				continue;
			}

			word[ len++ ] = rbuf[ i ];
		}

		if ( max_len == -1 )
			memcpy( &good_word, &rbuf, sizeof( char ) * MAX_STRING_SIZE );
		max_len = -1;

		vdvector_pushBack( &words, &good_word );
	}
	
	fclose( file );

	FILE *rd = fopen( "data/task05.txt", "w" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task05, "cannot open file task05.txt" );

	for ( size_t i = 0u; i < words.m_size; ++i ) {
		vdvector_get( &words, i, &rbuf );
		fprintf( rd, "%s\n", rbuf );
	}

	fclose( rd );
}

void task08( vdvector_t *ms ) {
	FILE *file = fopen( "data/task08.bin", "rb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task08, "cant open file task08.bin" );

	matrix_t mm;
	while ( fread( &mm, sizeof( matrix_t ), 1u, file ) == 1 ) {
		if ( !isSymmetricMatrix( &mm ) )
			transposeSquareMatrix( &mm );

		vdvector_pushBack( ms, &mm );
	}

	fclose( file );

	FILE *rd = fopen( "data/task08.bin", "wb" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task08, "cannot open file task08.bin" );

	for ( size_t i = 0u; i < ms->m_size; ++i ) {
		vdvector_get( ms, i, &mm );

		fwrite( &mm, sizeof( matrix_t ), 1u, rd );
	}

	fclose( rd );
}

void compareSportsmen( const void *pa, const void *pb ) {
	sportsman_t a = *( sportsman_t * )pa;
	sportsman_t b = *( sportsman_t * )pb;

	return b.m_result - a.m_result;
}

void task09( int n, vdvector_t *v ) {
	FILE *file = fopen( "data/task09.bin", "rb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( task09, "cant open file task09.bin" );

	vdvector_t sportsmen = vdvector_create( 0u, sizeof( sportsman_t ) );
	
	sportsman_t s;
	while ( fread( &s, sizeof( sportsman_t ), 1u, file ) == 1 ) {
		vdvector_pushBack( &sportsmen, &s );
	}

	fclose( file );

	qsort( sportsmen.m_data, sportsmen.m_size, sizeof( sportsman_t ), compareSportsmen );

	FILE *rd = fopen( "data/task09.bin", "wb" );
	if ( rd == NULL )
		STD_ERROR_N_EXIT( task09, "cannot open file task09.bin" );

	for ( size_t i = 0u; i < min( n, sportsmen.m_size ); ++i ) {
		vdvector_get( &sportsmen, i, &s );
		vdvector_pushBack( v, &s );
		fwrite( &s, sizeof( sportsman_t ), 1u, rd );
	}

	fclose( rd );
}

void task10( vdvector_t *v ) {
	FILE *f = fopen( "data/task10_f.bin", "rb" );
	if ( f == NULL )
		STD_ERROR_N_EXIT( task10, "cant open file task10_f.bin" );

	FILE *g = fopen( "data/task10_g.bin", "rb" );
	if ( g == NULL )
		STD_ERROR_N_EXIT( task10, "cant open file task10_g.bin" );

	vdvector_t procurements = vdvector_create( 0u, sizeof( procurement_t ) );

	procurement_t procurement;
	while ( fread( &procurement, sizeof( procurement_t ), 1u, g ) == 1 ) {
		vdvector_pushBack( &procurements, &procurement );
	}

	fclose( g );

	product_t product;
	while ( fread( &product, sizeof( product_t ), 1u, f ) == 1 ) {
		for ( size_t i = 0u; i < procurements.m_size; ++i ) {
			vdvector_get( &procurements, i, &procurement );
			if ( strcmp_( product.m_name, procurement.m_name ) == 0 ) {
				product.m_count -= procurement.m_count;
				product.m_full_price -= product.m_price * procurement.m_count;
			}
		}

		if ( product.m_count > 0 )
			vdvector_pushBack( v, &product );
	}

	fclose( f );

	FILE *fd = fopen( "data/task10_f.bin", "wb" );
	if ( fd == NULL )
		STD_ERROR_N_EXIT( task10, "cannot open file task10_f.bin" );

	for ( size_t i = 0u; i < v->m_size; ++i ) {
		vdvector_get( v, i, &product );

		fwrite( &product, sizeof( product_t ), 1u, fd );
	}

	fclose( fd );
}

void run_branch( ) {
	test_lab_content( );
}