#include "../include.h"

#include <assert.h>

#include <vdvector/include.h>
#include <matrix/include.h>
#include <file_manager/include.h>

#include "../../entry/include.h"

void test_task01( ) {
	vdvector_t tests = vdvector_create( 2u, sizeof( matrix_t ) );
	matrix_t m10 = createMatrixFromArray( ( int[ ] ) 
		{ 1, 2, 
		  3, 4 }, 2u, 2u 
	);

	matrix_t m11 = createMatrixFromArray( ( int[ ] ) 
		{ 1, 2, 3, 
		  4, 5, 6,
		  7, 8, 9 }, 3u, 3u 
	);

	vdvector_pushBack( &tests, &m10 );
	vdvector_pushBack( &tests, &m11 );

	gWriteMatrix( "data/task01.txt", tests );

	vdvector_t ms = vdvector_create( 2u, sizeof( matrix_t ) );
	matrix_t m00 = createMatrixFromArray( ( int[ ] ) 
		{ 1, 3, 
		  2, 4 }, 2u, 2u 
	);

	matrix_t m01 = createMatrixFromArray( ( int[ ] ) 
		{ 1, 4, 7, 
		  2, 5, 8,
		  3, 6, 9 }, 3u, 3u 
	);

	vdvector_pushBack( &ms, &m00 );
	vdvector_pushBack( &ms, &m01 );

	vdvector_t ret = vdvector_create( 0u, sizeof( matrix_t ) );
	task01( &ret );

	for ( size_t i = 0u; i < ms.m_size; ++i ) {
		matrix_t a, b;
		vdvector_get( &ms, i, &a );
		vdvector_get( &ret, i, &b );

		assert( a.m_rows == b.m_rows && a.m_cols == b.m_cols );
		for ( size_t j = 0u; j < a.m_rows; ++j )
			for ( size_t k = 0u; k < a.m_cols; ++k )
				assert( a.m_values[ j ][ k ] == b.m_values[ j ][ k ] );
	}
}

void test_lab_content( ) {
	test_task01( );
}