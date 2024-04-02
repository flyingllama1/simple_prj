#include "../include.h"

#include "../../tests/include.h"

#include <exceptions/include.h>

#include <vdvector/include.h>

#include <matrix/include.h>

#include <file_manager/include.h>

void task01( vdvector_t *ms ) {
	FILE *file = fopen( "data/task01.txt", "r" );
	if ( file == NULL )
		STD_ERROR( task01, "cannot open file task01.txt" );

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
		STD_ERROR( task02, "cannot open file task02.txt" );

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
		STD_ERROR( task03, "cannot open file task03.txt" );

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
	fprintf( write, "%d %c %d ", a, operation1, b );
	if ( had_one_more_operation )
		fprintf( write, "%c %d ", operation2, c );

	*v = ret;
}

void run_branch( ) {
	test_lab_content( );
}