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

void run_branch( ) {
	test_lab_content( );
}