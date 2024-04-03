#include "../include.h"

#include <assert.h>
#include <math.h>

#include <vdvector/include.h>

#include <matrix/include.h>

#include <file_manager/include.h>

#include <string/include.h>

#include <exceptions/include.h>

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
	if ( write == NULL )
		STD_ERROR_N_EXIT( test_task06, "cannot open file task06.bin" );

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
	if ( rd == NULL )
		STD_ERROR_N_EXIT( test_task07, "cannot open file task07.bin" );

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

void test_task04( ) {
	char *str = "aaa bc abe";
	gWriteLine( "data/task04.txt", str );

	task04( "b" );

	char *assertion1[ ] = { "bc", "abe" };
	FILE *file1 = fopen( "data/task04.txt", "r" );
	if ( file1 == NULL )
		STD_ERROR_N_EXIT( test_task04, "cannot open file task04.txt" );

	vdvector_t ret = vdvector_create( 0u, sizeof( char * ) );
	
	char rbuf[ MAX_STRING_SIZE ];
	while ( fscanf( file1, "%s", &rbuf ) == 1 )
		vdvector_pushBack( &ret, &rbuf );

	for ( size_t i = 0u; i < ret.m_size; ++i ) {
		vdvector_get( &ret, i, &rbuf );

		assert( strcmp_( rbuf, assertion1[ i ] ) == 0 );
	}

	fclose( file1 );

	vdvector_clear( &ret );

	gWriteLine( "data/task04.txt", str );
	task04( "aa" );

	char *assertion2[ ] = { "aaa" };

	FILE *file2 = fopen( "data/task04.txt", "r" );
	if ( file2 == NULL )
		STD_ERROR_N_EXIT( test_task04, "cannot open file task04.txt" );

	while ( fscanf( file2, "%s", &rbuf ) == 1 )
		vdvector_pushBack( &ret, &rbuf );

	for ( size_t i = 0u; i < ret.m_size; ++i ) {
		vdvector_get( &ret, i, &rbuf );

		assert( strcmp_( rbuf, assertion2[ i ] ) == 0 );
	}
}

void test_task05( ) {
	FILE *f = fopen( "data/task05.txt", "w" );
	if ( f == NULL )
		STD_ERROR_N_EXIT( test_task05, "cannot open file task05.txt" );

	fprintf( f, "aaa bc abe\n"
				"a\n"
				"\n"
				"ZZZZ bbbb cccc\n" );
	fclose( f );
	task05( NULL );
}

void test_task08( ) {
	int n = 3;
	int arr[ ] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9,
		1, 2, 1,
		2, 3, 2,
		1, 2, 1,
	};
	matrix_t *ms = createMatrixOfFromArray( arr, 2u, n, n );

	FILE *file = fopen( "data/task08.bin", "wb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( test_task08, "cannot open file task08.bin" );

	fwrite( ms, sizeof( matrix_t ) * 2u, 1u, file );
	fclose( file );

	vdvector_t ret = vdvector_create( 0u, sizeof( matrix_t ) );
	task08( &ret );

	for ( size_t i = 0u; i < 2u; ++i ) {
		matrix_t mm;
		vdvector_get( &ret, i, &mm );

		assert( areTwoMatricesEqual( &ms[ i ], &mm ) );
	}
}

void test_task09( ) {
	sportsman_t sportsmen[ ] = {
		{ "Ivanov I.I.", 20 },
		{ "Bashmak I.A.", 40 },
		{ "Shmurdak Z.G.", 119 },
		{ "Hurma J.J.", 19 },
		{ "Banditov B.B.",53 }
	};

	FILE *file = fopen( "data/task09.bin", "wb" );
	if ( file == NULL )
		STD_ERROR_N_EXIT( test_task09, "cannot open file task09.bin" );

	fwrite( sportsmen, sizeof( sportsman_t ), 5u, file );
	fclose( file );

	vdvector_t ret = vdvector_create( 3u, sizeof( sportsman_t ) );
	task09( 3, &ret );

	sportsman_t assertion[ ] = {
		{ "Shmurdak Z.G.", 119 },
		{ "Banditov B.B.",53 },
		{ "Bashmak I.A.", 40 },
	};

	for ( size_t i = 0u; i < 3u; ++i ) {
		sportsman_t s;
		vdvector_get( &ret, i, &s );

		assert( s.m_result == assertion[ i ].m_result );
	}
}

void test_task10( ) {
	product_t products[ ] = {
		{ "Meat", 10, 220, 22 },
		{ "Milk", 3, 33, 11 },
		{ "Bread", 1, 253, 253 },
	};

	procurement_t procurements[ ] = {
		{ "Meat", 7 },
		{ "Milk", 2 },
		{ "Bread", 20 },
		{ "Meat", 5 },
		{ "Bread", 105 },
		{ "Milk", 9 },
	};

	FILE *f = fopen( "data/task10_f.bin", "wb" );
	if ( f == NULL )
		STD_ERROR_N_EXIT( test_task10, "cannot open file task10_f.bin" );

	fwrite( products, sizeof( product_t ), 3u, f );
	fclose( f );

	FILE *g = fopen( "data/task10_g.bin", "wb" );
	if ( g == NULL )
		STD_ERROR_N_EXIT( test_task10, "cannot open file task10_g.bin" );

	fwrite( procurements, sizeof( procurement_t ), 6u, g );
	fclose( g );

	vdvector_t ret = vdvector_create( 0u, sizeof( product_t ) );
	task10( &ret );

	product_t assertion[ ] = {
		{ "Meat", 10, 100, 10 },
		{ "Bread", 1, 128, 128 },
	};

	assert( ret.m_size == 2u );
	for ( size_t i = 0u; i < 2u; ++i ) {
		product_t product;
		vdvector_get( &ret, i, &product );

		assert( strcmp_( product.m_name, assertion[ i ].m_name ) == 0 && product.m_full_price == assertion[ i ].m_full_price
			&& product.m_price == assertion[ i ].m_price && product.m_count == assertion[ i ].m_count );
	}
}

void test_lab_content( ) {
	test_task01( );

	test_task02( );

	test_task03( );

	test_task04( );
	
	test_task05( );

	test_task06( );

	test_task07( );
	
	test_task08( );

	test_task09( );

	test_task10( );
}