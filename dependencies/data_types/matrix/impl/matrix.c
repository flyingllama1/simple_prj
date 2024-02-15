#include "../include.h"

#include <stdio.h>
#include <memory.h>

#include <algorithm/include.h>

#include <exceptions/include.h>

#include <limits.h>

matrix_t getMemMatrix( int rows, int cols ) {
	matrix_t mat;

	mat.m_values = ( int ** )malloc( sizeof( int * ) * rows );
	for ( size_t i = 0u; i < rows; ++i )
		mat.m_values[ i ] = malloc( sizeof( int ) * cols );

	mat.m_cols = cols;
	mat.m_rows = rows;

	return mat;
}

matrix_t *getMemArrayOfMatrices( int matrices, int rows, int cols ) {
	matrix_t *ms = ( matrix_t * )malloc( sizeof( matrix_t ) * matrices );
	for ( size_t i = 0u; i < matrices; ++i )
		ms[ 0 ] = getMemMatrix( rows, cols );

	return ms;
}

void freeMemMatrix( matrix_t *mat ) {
	for ( size_t i = 0u; i < mat->m_rows; ++i )
		free( mat->m_values[ i ] );

	free( mat->m_values );

	mat->m_values = NULL;
}

void freeMemMatrices( matrix_t *mat, int matrices ) {
	for ( size_t i = 0u; i < matrices; ++i )
		freeMemMatrix( &mat[ i ] );
}

void inputMatrix( matrix_t *mat ) {
	for ( size_t i = 0u; i < mat->m_rows; ++i )
		for ( size_t j = 0u; j < mat->m_cols; ++j )
			scanf( "%d", &mat->m_values[ i ][ j ] );
}

void outputMatrix( const matrix_t mat ) {
	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		for ( size_t j = 0u; j < mat.m_cols; ++j ) {
			printf( "%d ", mat.m_values[ i ][ j ] );
		}

		printf( "\n" );
	}
}

void inputMatrices( matrix_t *mat, int matrices ) {
	for ( size_t i = 0u; i < matrices; ++i )
		inputMatrix( &mat[ i ] );
}

void outputMatrices( const matrix_t *mat, int matrices ) {
	for ( size_t i = 0u; i < matrices; ++i )
		outputMatrix( mat[ i ] );
}

void swapRows( matrix_t mat, int i, int j ) {
	int *imat = mat.m_values[ i ];

	memcpy( &mat.m_values[ i ], &mat.m_values[ j ], sizeof( int * ) );
	memcpy( &mat.m_values[ j ], &imat, sizeof( int * ) );
}

void swapColumns( matrix_t mat, int i, int j ) {
	for ( size_t k = 0u; k < mat.m_rows; ++k ) {
		int imat = mat.m_values[ k ][ i ];

		memcpy( &mat.m_values[ k ][ i ], &mat.m_values[ k ][ j ], sizeof( int ) );
		memcpy( &mat.m_values[ k ][ j ], &imat, sizeof( int ) );
	}
}

void insertionSortRowsMatrixByRowCriteria( matrix_t mat, int( *criteria )( int *, int ) ) {
	int *values = malloc( sizeof( int ) * mat.m_rows );
	for ( size_t i = 0u; i < mat.m_rows; ++i )
		values[ i ] = criteria( mat.m_values[ i ], mat.m_cols );

	for ( size_t i = 1u; i < mat.m_rows; ++i ) {
		int key = values[ i ];
		int j = i - 1;
		while ( key < values[ j ] && j >= 0 ) {
			values[ j + 1 ] = values[ j ];
			swapRows( mat, j + 1, j );
			--j;
		}

		values[ j + 1 ] = key;
	}
}

void selectionSortColsMatrixByColCriteria( matrix_t mat, int( *criteria )( int *, int ) ) {
	int *values = malloc( sizeof( int ) * mat.m_cols );
	for ( size_t i = 0u; i < mat.m_cols; ++i ) {
		int *col = malloc( sizeof( int ) * mat.m_rows );
		for ( size_t j = 0u; j < mat.m_rows; ++j )
			col[ j ] = mat.m_values[ j ][ i ];

		values[ i ] = criteria( col, mat.m_rows );
	}

	for ( int i = mat.m_cols - 1; i > 0; --i ) {
		int max = getMaxElementIndexInArray( values, i + 1 );
		if ( max != i ) {
			iswap( values + max, values + i );
			for ( size_t j = 0u; j < mat.m_rows; ++j )
				iswap( &mat.m_values[ j ][ max ], &mat.m_values[ j ][ i ] );
		}
	}
}

int isSquareMatrix( matrix_t *mat ) {
	return mat->m_rows == mat->m_cols;
}

int areTwoMatricesEqual( matrix_t *m1, matrix_t *m2 ) {
	if ( m1->m_cols != m2->m_cols
		|| m1->m_rows != m2->m_rows )
		return 0;

	for ( size_t i = 0u; i < m1->m_rows; ++i )
		if ( memcmp( m1->m_values[ i ], m2->m_values[ i ], sizeof( int ) * m1->m_cols ) )
			return 0;

	return 1;
}

int isEMatrix( matrix_t *mat ) {
	if ( !isSquareMatrix( mat ) )
		return 0;

	for ( size_t i = 0u; i < mat->m_rows; ++i ) {
		if ( mat->m_values[ i ][ i ] != 1 )
			return 0;

		for ( size_t j = 0u; j < mat->m_cols; ++j ) {
			if ( i != j && mat->m_values[ i ][ j ] != 0 )
				return 0;
		}
	}

	return 1;
}

int isSymmetricMatrix( matrix_t *mat ) {
	if ( !isSquareMatrix( mat ) )
		return 0;

	for ( size_t i = 0u; i < mat->m_rows; ++i ) {
		for ( size_t j = 0u; j < mat->m_cols; ++j ) {
			if ( mat->m_values[ i ][ j ] != mat->m_values[ j ][ i ] )
				return 0;
		}
	}

	return 1;
}

void transposeSquareMatrix( matrix_t *mat ) {
	if ( !isSquareMatrix( mat ) )
		return;

	for ( size_t i = 0u; i < mat->m_rows - 1; ++i ) {
		for ( size_t j = i + 1u; j < mat->m_rows; ++j ) {
			iswap( &mat->m_values[ i ][ j ], &mat->m_values[ j ][ i ] );
		}
	}
}

void transposeMatrix( matrix_t *mat ) {
	matrix_t res = getMemMatrix( mat->m_cols, mat->m_rows );

	for ( int col = 0; col < mat->m_cols; col++ ) {
		for ( int i = 0, j = col; i < mat->m_rows; i++ ) {
			res.m_values[ col ][ i ] = mat->m_values[ i ][ j ];
		}
	}

	memcpy( mat, &res, sizeof( matrix_t ) );
}

matpos_t getMinValuePos( matrix_t mat ) {
	matpos_t pos;
	int min = INT_MAX;

	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		for ( size_t j = 0u; j < mat.m_cols; ++j ) {
			if ( mat.m_values[ i ][ j ] < min ) {
				min = mat.m_values[ i ][ j ];
				pos.m_row = i + 1;
				pos.m_col = j + 1;
			}
		}
	}

	return pos;
}

matpos_t getMaxValuePos( matrix_t mat ) {
	matpos_t pos;
	int max = INT_MIN;

	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		for ( size_t j = 0u; j < mat.m_cols; ++j ) {
			if ( mat.m_values[ i ][ j ] > max ) {
				max = mat.m_values[ i ][ j ];
				pos.m_row = i + 1;
				pos.m_col = j + 1;
			}
		}
	}

	return pos;
}

matrix_t createMatrixFromArray( const int *array, int rows, int cols ) {
	matrix_t mat = getMemMatrix( rows, cols );
	int k = 0;
	for ( int i = 0; i < rows; ++i )
		for ( int j = 0; j < cols; ++j )
			mat.m_values[ i ][ j ] = array[ k++ ];

	return mat;
}

matrix_t *createMatrixOfFromArray( const int *values, int matrices, int rows, int cols ) {
	matrix_t *ms = getMemArrayOfMatrices( matrices, rows, cols );

	int l = 0;
	for ( size_t k = 0; k < matrices; ++k )
		for ( size_t i = 0; i < rows; ++i )
			for ( size_t j = 0; j < cols; ++j )
				ms[ k ].m_values[ i ][ j ] = values[ l++ ];

	return ms;
}

int getMax( int *a, int n ) {
	int max = a[ 0 ];
	for ( size_t i = 1u; i < n; ++i )
		if ( a[ i ] > max )
			max = a[ i ];

	return max;
}

void sortRowsByMinElement( matrix_t mat ) {
	insertionSortRowsMatrixByRowCriteria( mat, getMax );
}

int getMin( int *a, int n ) {
	int min = a[ 0 ];
	for ( size_t i = 1u; i < n; ++i )
		if ( min >= a[ i ] )
			min = a[ i ];

	return min;
}

void sortColsByMinElement( matrix_t mat ) {
	int *values = malloc( sizeof( int ) * mat.m_cols );
	for ( size_t i = 0u; i < mat.m_cols; ++i ) {
		int *col = malloc( sizeof( int ) * mat.m_rows );
		for ( size_t j = 0u; j < mat.m_rows; ++j )
			col[ j ] = mat.m_values[ j ][ i ];

		values[ i ] = getMin( col, mat.m_rows );
	}

	for ( int i = 0; i < mat.m_cols; ++i ) {
		int max = getMaxElementIndexInArray( values, i + 1 );
		if ( max != i ) {
			iswap( values + max, values + i );
			for ( size_t j = 0u; j < mat.m_rows; ++j )
				iswap( &mat.m_values[ j ][ max ], &mat.m_values[ j ][ i ] );
		}
	}
}

matrix_t mulMatrices( matrix_t *m1, matrix_t *m2 ) {
	if ( m1->m_cols != m2->m_rows ) {
		STD_ERROR_N_EXIT( mulMatrices, "the operation cannot be performed with the resulting matrices." );
	}

	matrix_t res = getMemMatrix( m1->m_rows, m2->m_cols );
	//memset( res.m_values, 0, sizeof( int ) * res.m_rows * res.m_cols );

	for ( size_t i = 0u; i < res.m_rows; ++i ) {
		for ( size_t j = 0u; j < res.m_cols; ++j ) {
			res.m_values[ i ][ j ] = 0;
			for ( size_t k = 0u; k < m1->m_cols; ++k ) {
				res.m_values[ i ][ j ] += m1->m_values[ i ][ k ] * m2->m_values[ k ][ j ];
			}
		}
	}

	return res;
}

int isUnique( long long *a, int n ) {
	for ( size_t i = 0u; i < n; ++i )
		for ( size_t j = i + 1u; j < n; ++j )
			if ( a[ i ] == a[ j ] )
				return 0;

	return 1;
}

long long getLongSum( int *a, int n ) {
	long long res = 0ll;

	for ( size_t i = 0; i < n; ++i )
		res += a[ i ];

	return res;
}

void transposeIfMatrixHasNotEqualSumOfRows( matrix_t *mat ) {
	long long *values = ( long long * )malloc( sizeof( long long ) * mat->m_rows );
	for ( size_t i = 0u; i < mat->m_rows; ++i )
		values[ i ] = getLongSum( mat->m_values[ i ], mat->m_cols );

	if ( isUnique( values, mat->m_rows ) ) {
		transposeMatrix( mat );
	}
}