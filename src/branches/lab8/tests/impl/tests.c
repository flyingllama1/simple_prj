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
	int n0 = 3u;
	matrix_t mm0 = getMemMatrix( n0, n0 );

	int queries0[ ][ 4u ] = {
		{ 1, 1, 2, 2 },
		{ 0, 0, 1, 1 },
	};

	task01( &mm0, queries0, 2u );

	matrix_t assertion0 = createMatrixFromArray( ( int[ ] ) { 1, 1, 0, 1, 2, 1, 0, 1, 1 }, n0, n0 );
	assert( areTwoMatricesEqual( &mm0, &assertion0 ) );

	int n1 = 5u;
	matrix_t mm1 = getMemMatrix( n1, n1 );

	int queries1[ ][ 4u ] = {
		{ 1, 3, 3, 4 },
		{ 2, 1, 3 ,3 },
		{ 1, 1, 4 ,3 },
		{ 0, 0, 3, 1 },
	};

	task01( &mm1, queries1, 4u );
	
	matrix_t assertion1 = createMatrixFromArray( ( int[ ] ) { 1, 1, 0, 0, 0, 1, 2, 1, 2, 1, 1, 3, 2, 3, 1, 1, 3, 2, 3, 1, 0, 1, 1, 1, 0 }, n1, n1 );
	assert( areTwoMatricesEqual( &mm1, &assertion1 ) );

	printf( "task01 - OK\n" );
}

void test_task02( ) {
	matrix_t board0 = createMatrixFromArray( ( int[ ] ) { 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 }, 4u, 3u );
	matrix_t next_gen0 = getMemMatrix( 4u, 3u );
	task02( &board0, &next_gen0 );

	matrix_t assertion0 = createMatrixFromArray( ( int[ ] ) { 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0 }, 4u, 3u );
	assert( areTwoMatricesEqual( &next_gen0, &assertion0 ) );

	matrix_t board1 = createMatrixFromArray( ( int[ ] ) { 
		1, 0, 0, 1, 1, 0, 1, 
		0, 1, 0, 0, 0, 0, 0, 
		0, 0, 0, 1, 1, 0, 0, 
		1, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 1, 0, 
		0, 0, 1, 0, 0, 0, 0, 
		1, 0, 0, 0, 1, 1, 0 
	}, 7, 7 );
	matrix_t next_gen1 = getMemMatrix( 7u, 7u );
	task02( &board1, &next_gen1 );

	matrix_t assertion1 = createMatrixFromArray( ( int[ ] ) {
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0
	}, 7u, 7u );
	
	assert( areTwoMatricesEqual( &next_gen1, &assertion1 ) );

	printf( "task02 - OK\n" );
}

void test_lab_content( ) {
	test_task01( );

	test_task02( );
}