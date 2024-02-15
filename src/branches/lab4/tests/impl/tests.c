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

void test_matrix_content( ) {
	test_task01( );

	test_task02( );

	test_task03( );

	test_task04( );
}