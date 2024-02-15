#include "../include.h"

#include <assert.h>

#include <matrix/include.h>

#include "../../entry/include.h"

void test_matrix_content( ) {
	matrix_t mat = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			4, 3, 2, 1,
			1, 1, 1, 1,
			5, 2, 4, 4
		}, 4, 4
	);

	task01( &mat );

	matrix_t res1 = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			5, 2, 4, 4,
			1, 1, 1, 1,
			4, 3, 2, 1,
		}, 4, 4
	);

	assert( areTwoMatricesEqual( &mat, &res1 ) == 1 );
}