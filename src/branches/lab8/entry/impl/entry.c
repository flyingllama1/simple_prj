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

void run_branch( ) {
	test_lab_content( );
}