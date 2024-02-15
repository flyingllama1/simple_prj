#include "../include.h"

#include <matrix/include.h>

#include "../../tests/include.h"

#include <algorithm/include.h>

void task01( matrix_t *mat ) {
	int min_val = mat->m_values[ 0 ][ 0 ];
	int max_val = mat->m_values[ 0 ][ 0 ];

	int min_row = 0;
	int max_row = 0;

	for ( size_t i = 0u; i < mat->m_rows; ++i ) {
		for ( size_t j = 0u; j < mat->m_cols; ++j ) {
			if ( mat->m_values[ i ][ j ] > max_val ) {
				max_val = mat->m_values[ i ][ j ];
				max_row = i;
			}
			else if ( mat->m_values[ i ][ j ] < min_val ) {
				min_val = mat->m_values[ i ][ j ];
				min_row = i;
			}
		}
	}

	swapRows( *mat, min_row, max_row );
}

void task02( matrix_t *mat ) {
	sortRowsByMinElement( *mat );
}

void task03( matrix_t *mat ) {
	sortColsByMinElement( *mat );
}

void task04( matrix_t *mat, matrix_t *res ) {
	if ( isSymmetricMatrix( mat ) )
		*res = mulMatrices( mat, mat );
	else
		*res = *mat;
}

void task05( matrix_t *mat ) {
	transposeIfMatrixHasNotEqualSumOfRows( mat );
}

int task06( matrix_t *m1, matrix_t *m2 ) {
	int ret = isMutuallyInverseMatrices( *m1, *m2 );

	return ret;
}

long long task07( matrix_t *mat ) {
	return findSumOfMaxesOfPseudoDiagonal( *mat );
}

void run_branch( ) {
	test_matrix_content( );
}