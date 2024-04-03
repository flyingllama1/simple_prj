#include "../include.h"

#include <assert.h>
#include <math.h>

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

void test_task02( ) {
	vdvector_t tests = vdvector_create( 5u, sizeof( float ) );
	float arr[ ] = { 1.0f, 2.2224f, 1.337f, 0, -4.0001f };
	for ( size_t i = 0u; i < 5u; ++i )
		vdvector_pushBack( &tests, &arr[ i ] );

	gWriteFloat( "data/task02.txt", tests, "%f " );

	vdvector_t v = vdvector_create( 5u, sizeof( float ) );
	float v_arr[ ] = { 1.0f, 2.22f, 1.33f, 0.00f, -4.00f };

	vdvector_t ret = vdvector_create( 0u, sizeof( float ) );
	task02( &ret );

	for ( size_t i = 0u; i < v.m_size; ++i ) {
		float a, b;
		vdvector_get( &v, i, &a );
		vdvector_get( &ret, i, &b );

		assert( fabsf( a - b ) < 0.000001f );
	}
}

void test_task03( ) {
	int ret;
	
	gWriteLine( "data/task03.txt", "2 + 5" );
	task03( &ret );
	assert( ret == 7 );

	gWriteLine( "data/task03.txt", "2 + 5 + 3" );
	task03( &ret );
	assert( ret == 10 );

	gWriteLine( "data/task03.txt", "2 + 5 * 3" );
	task03( &ret );
	assert( ret == 17 );

	gWriteLine( "data/task03.txt", "2 * 6 / 3" );
	task03( &ret );
	assert( ret == 4 );
	
	gWriteLine( "data/task03.txt", "2 * 5 + 0" );
	task03( &ret );
	assert( ret == 10 );
}

void test_task06( ) {
	polynomial_t poly[ 4u ] = { 
		{ 3, 1 },
		{ 2, 1 },
		{ 1, -1 },
		{ 0, -1 },
	};

	FILE *write = fopen( "data/task06.bin", "wb+" );
	fwrite( poly, sizeof( polynomial_t ), 4u, write );
	fclose( write );
	
	vdvector_t ret = vdvector_create( 0u, sizeof( polynomial_t ) );
	task06( -1.f, &ret );

	assert( ret.m_size == 3u );
	polynomial_t assertion[ 3u ] = {
		{ 3, 1 },
		{ 1, -1 },
		{ 0, -1 },
	};

	for ( size_t i = 0u; i < ret.m_size; ++i ) {
		polynomial_t p;
		vdvector_get( &ret, i, &p );

		assert( p.m_coeff == assertion[ i ].m_coeff && p.m_power == assertion[ i ].m_power );
	}
}

void test_task07( ) {
	int arr[ ] = { 1, -2, 4, 2, -9, -1 };
	FILE *rd = fopen( "data/task07.bin", "wb" );
	fwrite( &arr, sizeof( int ), 6u, rd );
	fclose( rd );

	vdvector_t nums = vdvector_create( 6u, sizeof( int ) );

	task07( &nums );

	vdvector_t assertion = vdvector_create( 6u, sizeof( int ) );
	vdvector_pushBack( &assertion, &arr[ 0 ] );
	vdvector_pushBack( &assertion, &arr[ 2 ] );
	vdvector_pushBack( &assertion, &arr[ 3 ] );
	vdvector_pushBack( &assertion, &arr[ 1 ] );
	vdvector_pushBack( &assertion, &arr[ 4 ] );
	vdvector_pushBack( &assertion, &arr[ 5 ] );

	for ( size_t i = 0u; i < assertion.m_size; ++i ) {
		int n, a;
		vdvector_get( &nums, i, &n );
		vdvector_get( &assertion, i, &a );

		assert( n == a );
	}
}

void test_lab_content( ) {
	test_task01( );

	test_task02( );

	test_task03( );

	test_task06( );

	test_task07( );
}