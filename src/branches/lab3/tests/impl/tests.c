#include "../include.h"

#include <assert.h>

#include <matrix/include.h>

int getSum( int *a, int n ) {
	int s = 0;
	for ( size_t i = 0u; i < n; ++i )
		s += a[ i ];

	return s;
}

void test_matrix_content( ) {
	matrix_t mat = getMemMatrix( 4, 4 );
	assert( 
		mat.m_values != NULL
		&& mat.m_rows == 4 && mat.m_cols == 4
	);
	
	freeMemMatrix( &mat );
	mat = createMatrixFromArray(
		( int[ ] ) {
			1, 0, 0, 1,
			0, 2, 2, 0,
			0, 2, 2, 0,
			1, 0, 0, 1
		}, 4, 4
	);

	assert(
		mat.m_values != NULL
		&& mat.m_rows == 4 && mat.m_cols == 4
	);

	assert( isSymmetricMatrix( &mat ) == 1 );

	freeMemMatrix( &mat );
	mat = createMatrixFromArray(
		( int[ ] ) {
			1, 2, 3, 4,
			4, 3, 2, 1,
			1, 1, 1, 1,
			1, 0, 0, 1
		}, 4, 4
	);

	matrix_t eq = createMatrixFromArray(
		( int[ ] ) {
			1, 2, 3, 4,
			4, 3, 2, 1,
			1, 1, 1, 1,
			1, 0, 0, 1
		}, 4, 4
	);
	assert( isSquareMatrix( &mat ) == 1 );

	assert( isSymmetricMatrix( &mat ) == 0 );
	assert( areTwoMatricesEqual( &mat, &eq ) == 1 );

	freeMemMatrix( &mat );
	mat = createMatrixFromArray(
		( int[ ] ) {
			2, 2, 3, 4,
			4, 3, 2, 1,
			1, 1, 1, 1,
		}, 3, 4
	);

	assert( areTwoMatricesEqual( &mat, &eq ) == 0 );
	assert( isSquareMatrix( &mat ) == 0 );

	transposeMatrix( &mat );
	matrix_t tr = createMatrixFromArray(
		( int[ ] ) {
			2, 4, 1,
			2, 3, 1,
			3, 2, 1,
			4, 1, 1
		}, 4, 3
	);

	assert( areTwoMatricesEqual( &mat, &tr ) == 1 );

	matrix_t trs = createMatrixFromArray(
		( int[ ] ) {
			1, 4, 1, 1,
			2, 3, 1, 0,
			3, 2, 1, 0,
			4, 1, 1, 1,
		}, 4, 4
	);
	transposeSquareMatrix( &eq );

	assert( areTwoMatricesEqual( &trs, &eq ) == 1 );

	freeMemMatrix( &mat );
	mat = createMatrixFromArray(
		( int[ ] ) {
			2, 4, 1,
			2, 3, 1,
			3, 2, 1,
			4, 1, 1
		}, 4, 3
	);

	insertionSortRowsMatrixByRowCriteria( mat, getSum );

	matrix_t isr = createMatrixFromArray(
		( int[ ] ) {
			2, 3, 1,
			3, 2, 1,
			4, 1, 1,
			2, 4, 1
		}, 4, 3
	);

	assert( areTwoMatricesEqual( &isr, &mat ) == 1 );

	selectionSortColsMatrixByColCriteria( mat, getSum );

	matrix_t ssc = createMatrixFromArray(
		( int[ ] ) {
			1, 3, 2,
			1, 2, 3,
			1, 1, 4,
			1, 4, 2,
		}, 4, 3
	);

	assert( areTwoMatricesEqual( &ssc, &mat ) == 1 );

	matpos_t max = getMaxValuePos( mat );
	matpos_t min = getMinValuePos( mat );

	assert(
		max.m_row == 3 && max.m_col == 3
	);

	assert(
		min.m_row == 1 && min.m_col == 1
	);

	swapColumns( mat, 0, 1 );
	swapRows( mat, 0, 1 );
	
	matrix_t res = createMatrixFromArray(
		( int[ ] ) {
			2, 1, 3,
			3, 1, 2,
			1, 1, 4,
			4, 1, 2,
		}, 4, 3
	); 

	assert(
		areTwoMatricesEqual( &res, &mat ) == 1
	);

	freeMemMatrix( &res );
	assert( res.m_values == NULL );
}