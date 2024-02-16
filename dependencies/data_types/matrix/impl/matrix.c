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
		ms[ i ] = getMemMatrix( rows, cols );

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
			swapInt( values + max, values + i );
			for ( size_t j = 0u; j < mat.m_rows; ++j )
				swapInt( &mat.m_values[ j ][ max ], &mat.m_values[ j ][ i ] );
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
			swapInt( &mat->m_values[ i ][ j ], &mat->m_values[ j ][ i ] );
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
			swapInt( values + max, values + i );
			for ( size_t j = 0u; j < mat.m_rows; ++j )
				swapInt( &mat.m_values[ j ][ max ], &mat.m_values[ j ][ i ] );
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

int isMutuallyInverseMatrices( matrix_t m1, matrix_t m2 ) {
	if ( m1.m_rows != m2.m_rows
		|| m1.m_cols != m2.m_rows )
		return 0;

	for ( size_t i = 0u; i < m1.m_rows; ++i ) {
		for ( size_t j = 0u; j < m2.m_cols; ++j ) {
			int sum = 0;
			for ( size_t k = 0u; k < m1.m_cols; ++k )
				sum += ( m1.m_values[ i ][ k ] * m2.m_values[ k ][ j ] );

			if ( sum != ( i == j ) )
				return 0;
		}
	}

	return 1;
}

long long findSumOfMaxesOfPseudoDiagonal( matrix_t mat ) {
	for ( size_t i = 0u; i < mat.m_rows; ++i )
		mat.m_values[ i ][ i ] = 0;

	long long ret = 0ll;
	for ( size_t i = 0u; i < mat.m_cols + mat.m_rows - 1u; ++i ) {
		int row = max2( 0, mat.m_rows - i - 1 );
		int col = max2( 0, i - mat.m_rows + 1 );

		int max_value = INT_MIN;
		while ( row < mat.m_rows
			&& col < mat.m_cols ) {
			max_value = max2( max_value, mat.m_values[ row ][ col ] );
			
			++row;
			++col;
		}

		ret += max_value;
	}

	return ret;
}

int getMinInArea( matrix_t mat ) {
	matpos_t max = getMaxValuePos( mat );

	int res = INT_MAX;
	for ( size_t i = 0u; i < max.m_row; ++i ) {
		for ( size_t j = 0u; j < max.m_col; ++j ) {
			if ( abs( max.m_col - j ) <= abs( max.m_row - i ) ) {
				res = min2( res, mat.m_values[ i ][ j ] );
			}
		}
	}

	return res;
}

void insertionSortRowsMatrixByRowCriteriaF( matrix_t mat, float ( *criteria )( int *, int ) ) {
	float *values = malloc( sizeof( int ) * mat.m_rows );
	for ( size_t i = 0u; i < mat.m_rows; ++i )
		values[ i ] = criteria( mat.m_values[ i ], mat.m_cols );

	for ( size_t i = 1u; i < mat.m_rows; ++i ) {
		float key = values[ i ];
		int j = i - 1;
		while ( key < values[ j ] && j >= 0 ) {
			values[ j + 1 ] = values[ j ];
			swapRows( mat, j + 1, j );
			--j;
		}

		values[ j + 1 ] = key;
	}
}

void sortByDistances( matrix_t *mat ) {
	insertionSortRowsMatrixByRowCriteriaF( *mat, getDistance );
}

int cmp_long_long( const void *a, const void *b ) {
	return *( const int * )a - *( const int * )b;
}

int countNUnique( long long *array, const size_t size ) {
	int count = 1;
	
	long long record = array[ 0 ];
	for ( size_t i = 1; i < size; ++i ) {
		if ( array[ i ] != record ) {
			++count;
			record = array[ i ];
		}
	}

	return count;
}

int countEqClassesByRowsSum( matrix_t mat ) {
	long long *values = ( long long * )malloc( sizeof( long long ) * mat.m_rows );
	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		long long sum = 0ll;
		for ( size_t j = 0u; j < mat.m_cols; ++j )
			sum += mat.m_values[ i ][ j ];

		values[ i ] = sum;
	}

	qsort( values, mat.m_rows, sizeof( long long ), cmp_long_long );
	
	return countNUnique( values, mat.m_rows );
}

int getNSpecialElement( matrix_t mat ) {
	int ret = 0;

	for ( size_t i = 0u; i < mat.m_cols; ++i ) {
		int sum = 0;
		for ( size_t j = 0u; j < mat.m_rows; ++j ) {
			sum += mat.m_values[ j ][ i ];
		}

		for ( size_t j = 0u; j < mat.m_rows; ++j ) {
			if ( mat.m_values[ j ][ i ] > ( sum - mat.m_values[ j ][ i ] ) )
				++ret;
		}
	}

	return ret;
}

void swapPenultimateRow( matrix_t *mat ) {
	matpos_t pos = getMinValuePos( *mat );

	int temp = mat->m_values[ mat->m_rows - ( mat->m_rows - 1u ) ][ pos.m_col - 1u ];
	for ( size_t i = 0u; i < mat->m_cols; ++i )
		mat->m_values[ mat->m_rows - 2u ][ i ] = mat->m_values[ i ][ pos.m_col - 1u ];

	mat->m_values[ mat->m_rows - 2u ][ 1u ] = temp;
}

int hasAllNonDescendingRows( matrix_t mat ) {
	for ( size_t i = 0u; i < mat.m_rows; ++i )
		if ( !isNonDescendingSorted( mat.m_values[ i ], mat.m_cols ) )
			return 0;

	return 1;
}

int countNonDescendingRowsMatrices( matrix_t *ms, int matrices_amount ) {
	int ret = 0;
	for ( size_t i = 0u; i < matrices_amount; ++i )
		if ( hasAllNonDescendingRows( ms[ i ] ) )
			++ret;

	return ret;
}

int countZeroRows( matrix_t mat ) {
	int ret = 0;
	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		int amt = countValues( mat.m_values[ i ], mat.m_cols, 0 );
		if ( amt == mat.m_cols )
			++ret;
	}

	return ret;
}

void printMatrixWithMaxZeroRows( matrix_t *ms, int matrices_amount ) {
	int max_rows = INT_MIN;

	for ( size_t i = 0u; i < matrices_amount; ++i ) {
		int amt = countZeroRows( ms[ i ] );
		
		max_rows = max2( max_rows, amt );
	}

	for ( size_t i = 0u; i < matrices_amount; ++i ) {
		int amt = countZeroRows( ms[ i ] );
		if ( amt == max_rows )
			outputMatrix( ms[ i ] );
	}
}

int getMatrixNorm( const matrix_t mat ) {
	int ret = 0;
	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		for ( size_t j = 0u; j < mat.m_cols; ++j ) {
			int norm = abs( mat.m_values[ i ][ j ] );
			ret = max2( ret, norm );
		}
	}

	return ret;
}
void printMatrixWithMinNorm( matrix_t *ms, int matrices_amount ) {
	int min_norm = INT_MAX;

	for ( size_t i = 0u; i < matrices_amount; ++i ) {
		int norm = getMatrixNorm( ms[ i ] );

		min_norm = min2( min_norm, norm );
	}

	for ( size_t i = 0u; i < matrices_amount; ++i ) {
		int norm = getMatrixNorm( ms[ i ] );

		if ( norm == min_norm )
			outputMatrix( ms[ i ] );
	}
}

int getNSpecialElement2( matrix_t mat ) {
	int ret = 0;
	for ( size_t i = 0u; i < mat.m_rows; ++i ) {
		for ( size_t j = 0u; j < mat.m_cols; ++j ) {
			int is_decreasing = 1;
			int is_increasing = 1;
			for ( size_t k = 0u; k < mat.m_cols; ++k ) {
				if ( k > j
					&& mat.m_values[ i ][ j ] > mat.m_values[ i ][ k ] )
					is_increasing = 0;
				if ( k < j
					&& mat.m_values[ i ][ j ] < mat.m_values[ i ][ k ] )
					is_decreasing = 0;
			}

			if ( is_increasing && is_decreasing ) {
				++ret;
			}
		}
	}

	return ret;
}