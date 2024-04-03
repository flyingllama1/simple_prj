#include "../include.h"

#include "../../tests/include.h"

#include <exceptions/include.h>

#include <vdvector/include.h>

#include <matrix/include.h>

#include <file_manager/include.h>

#include <string/include.h>

void task01( matrix_t *mm, int queries[ ][ 4 ], const size_t queries_amt ) {
	for ( size_t i = 0u; i < queries_amt; ++i ) {
		int *query = queries[ i ];
		for ( size_t row = query[ 0 ]; row <= query[ 2 ]; ++row ) {
			for ( size_t col = query[ 1 ]; col <= query[ 3 ]; ++col ) {
				mm->m_values[ row ][ col ] += 1;
			}
		}
	}
}

int countNeighbourPoints( matrix_t *mm, int row, int col ) {
	int left = max( 0, col - 1 );
	int head = max( 0, row - 1 );
	int right = min( mm->m_cols - 1u, col + 1 );
	int bot = min( mm->m_rows - 1u, row + 1 );

	int neighbours = 0;
	for ( size_t i = head; i <= bot; ++i )
		for ( size_t j = left; j <= right; ++j )
			if ( mm->m_values[ i ][ j ] == 1 && ( col != j || row != i ) )
				++neighbours;

	return neighbours;
}

void task02( matrix_t *m0, matrix_t *m1 ) {
	for ( size_t i = 0u; i < m0->m_rows; ++i ) {
		for ( size_t j = 0u; j < m0->m_cols; ++j ) {
			int neighbours = countNeighbourPoints( m0, i, j );

			m1->m_values[ i ][ j ] = 1;
			if ( m0->m_values[ i ][ j ] == 1 ) {
				if ( neighbours < 2 || neighbours > 3 )
					m1->m_values[ i ][ j ] = 0;
			}
			else {
				if ( neighbours != 3 )
					m1->m_values[ i ][ j ] = 0;
			}
		}
	}
}

void run_branch( ) {
	test_lab_content( );
}