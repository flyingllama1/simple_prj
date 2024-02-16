#include "../include.h"

#include <assert.h>

#include <matrix/include.h>

#include "../../entry/include.h"

void test_task01( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			4, 3, 2, 1,
			1, 1, 1, 1,
			5, 2, 4, 4
		}, 4, 4
	);

	task01( &mat );

	matrix_t res = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			5, 2, 4, 4,
			1, 1, 1, 1,
			4, 3, 2, 1,
		}, 4, 4
	);

	assert( areTwoMatricesEqual( &mat, &res ) == 1 );
}

void test_task02( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			3, 3, 2, 1,
			1, 1, 1, 1,
			5, 2, 4, 4
		}, 4, 4
	);

	task02( &mat );

	matrix_t res = createMatrixFromArray(
		( int[ ] ) {
			1, 1, 1, 1,
			3, 3, 2, 1,
			2, 2, 3, 4,
			5, 2, 4, 4,
		}, 4, 4
	);

	assert( areTwoMatricesEqual( &mat, &res ) == 1 );
}

void test_task03( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			3, 5, 2, 4, 3, 3,
			2, 5, 1, 8, 2, 7,
			6, 1, 4, 4, 8, 3,
		}, 3, 6
	);

	task03( &mat );

	matrix_t res = createMatrixFromArray(
		( int[ ] ) {
			5, 2, 3, 3, 3, 4,
			5, 1, 2, 2, 7, 8,
			1, 4, 6, 8, 3, 4,
		}, 3, 6
	);

	assert( areTwoMatricesEqual( &mat, &res ) == 1 );
}

void test_task04( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			1, 0, 0, 1,
			0, 2, 2, 0,
			0, 2, 2, 0,
			1, 0, 0, 1
		}, 4, 4
	);

	matrix_t ret;
	task04( &mat, &ret );

	matrix_t res = createMatrixFromArray(
		( int[ ] ) {
			2, 0, 0, 2,
			0, 8, 8, 0,
			0, 8, 8, 0,
			2, 0, 0, 2,
		}, 4, 4
	);

	assert( areTwoMatricesEqual( &ret, &res ) == 1 );
}

void test_task05A( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			1, 2, 3,
			4, 5, 6,
			7, 8, 9,
		}, 3, 3
	);

	task05( &mat );

	matrix_t ret = createMatrixFromArray(
		( int[ ] ) {
			1, 4, 7,
			2, 5, 8,
			3, 6, 9
		}, 3, 3
	);

	assert( areTwoMatricesEqual( &mat, &ret ) == 1 );
}

void test_task05B( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			7, 4, 4,
			4, 5, 6,
			7, 8, 9,
		}, 3, 3
	);

	task05( &mat );

	matrix_t ret = createMatrixFromArray(
		( int[ ] ) {
			1, 4, 7,
			2, 5, 8,
			2, 6, 9
		}, 3, 3
	);

	assert( areTwoMatricesEqual( &mat, &ret ) == 0 );
}

void test_task06A( ) {
	matrix_t m1 = createMatrixFromArray(
		( int[ ] ) {
			1, -2, 1,
			2, 1, -1,
			3, 2, -2
		}, 3, 3
	);

	matrix_t m2 = createMatrixFromArray(
		( int[ ] ) {
			0, 2, -1,
			-1, 5, -3,
			-1, 8, -5
		}, 3, 3
	);

	int ret = task06( &m1, &m2 );

	assert( ret == 1 );
}

void test_task06B( ) {
	matrix_t m1 = createMatrixFromArray(
		( int[ ] ) {
			1, -2, 1,
			1, 1, -1,
			3, 2, -2
		}, 3, 3
	);

	matrix_t m2 = createMatrixFromArray(
		( int[ ] ) {
			0, 2, -1,
			-1, 5, -3,
			-1, 8, -5
		}, 3, 3
	);

	int ret = task06( &m1, &m2 );

	assert( ret == 0 );
}

void test_task07( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			3, 2, 5, 4,
			1, 3, 6, 3,
			3, 2, 1, 2
		}, 3, 4
	);

	long long ans = task07( &mat );

	assert( ans == 20 );
}

void test_task08A( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			10, 7, 5, 6,
			3, 11, 8, 9,
			4, 1, 12, 2
		}, 3, 4
	);

	int ret = getMinInArea( mat );

	assert( ret == 5 );
}

void test_task08B( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			6, 8, 9, 2,
			7, 12, 3, 4,
			10, 11, 5, 1
		}, 3, 4
	);

	int ret = getMinInArea( mat );

	assert( ret == 6 );
}

void test_task09( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			5, 11,
			2, 12,
			11, 3,
			4, 2
		}, 4, 2
	);

	task09( &mat );
	
	matrix_t ret = createMatrixFromArray(
		( int[ ] ) {
			4, 2,
			11, 3,
			5, 11,
			2, 12
		}, 4, 2
	);

	assert( areTwoMatricesEqual( &mat, &ret ) == 1 );
}

void test_task10( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			7, 1,
			2, 7,
			5, 4,
			4, 3,
			1, 6,
			8, 0
		}, 6, 2
	);

	int ret = task10( &mat );

	assert( ret == 3 );
}

void test_task11( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			3, 5, 5, 4,
			2, 3, 6, 7,
			12, 2, 1, 2
		}, 3, 4
	);

	int ret = task11( &mat );

	assert( ret == 2 );
}

void test_task12( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			1, 2, 3,
			4, 5, 6,
			7, 8, 1
		}, 3, 3
	);

	task12( &mat );

	matrix_t ret = createMatrixFromArray(
		( int[ ] ) {
			1, 2, 3,
			1, 4, 7,
			7, 8, 1
		}, 3, 3
	);

	assert( areTwoMatricesEqual( &mat, &ret ) == 1 );
}

void test_task13( ) {
	matrix_t *ms = createMatrixOfFromArray(
		( int[ ] ) {
			7, 1,
			1, 1,
			1, 6,
			2, 2,
			5, 4,
			2, 3,
			1, 3,
			7, 9
		}, 
		4, 
		2, 2
	);

	int ret = task13( ms, 4 );

	assert( ret == 2 );
}

void test_task14( ) {
	matrix_t *ms = createMatrixOfFromArray(
		( int[ ] ) {
			0, 1,
			1, 0,
			0, 0,
			1, 1,
			2, 1,
			1, 1,
			0, 0,
			0, 0,
			4, 7,
			0, 0,
			1, 0,
			0, 0,
			0, 1,
			0, 2,
			0, 3,
		}, 
		4, 
		3, 2
	);

	printf(
		"task14:\n"
		"expected result:\n"
		"0 0\n"
		"0 0\n"
		"4 7\n"
		"0 0\n"
		"1 0\n"
		"0 0\n"
		"algorithm result:\n"
	);

	task14( ms, 4u );

	printf( "\n" );
}

void test_task15( ) {
	matrix_t *ms = createMatrixOfFromArray(
		( int[ ] ) {
			1, 3,
			5, 2,
			2, 4,
			6, 8,
			4, 1,
			9, 1,
			2, 2,
			2, 2
		},
		4, 
		2, 2
	);

	printf(
		"task15:\n"
		"expected result:\n"
		"2 2\n"
		"2 2\n"
		"algorithm result:\n"
	);

	task15( ms, 4u );

	printf( "\n" );
}

void test_task16( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			2, 3, 5, 5, 4,
			6, 2, 3, 8, 12,
			12, 12, 2, 1, 2
		}, 3, 5
	);

	int ret = task16( &mat );

	assert( ret == 4 );
}

void test_matrix_content( ) {
	test_task01( );

	test_task02( );

	test_task03( );

	test_task04( );

	test_task05A( );

	test_task05B( );

	test_task06A( );
	
	test_task06B( );

	test_task07( );

	test_task08A( );

	test_task08B( );

	test_task09( );

	test_task10( );

	test_task11( );

	test_task12( );

	test_task13( );

	test_task14( );

	test_task15( );

	test_task16( );
}