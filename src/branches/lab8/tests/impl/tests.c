#include "../include.h"

#include <assert.h>
#include <math.h>

#include <vector/include.h>
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

void test_task03( ) {
	int filter = 3;
	matrix_t m00 = createMatrixFromArray( ( int[ ] ) { 10, 20, 30, 25, 35, 45, 15, 25, 35 }, filter, filter );
	matrix_t m01 = getMemMatrix( filter, filter );

	task03( &m00, &m01 );
	
	matrix_t assertion0 = createMatrixFromArray( ( int[ ] ) { 10, 20, 30, 25, 25, 45, 15, 25, 35 }, filter, filter );

	printf( "task03 - OK\n" );
}

void test_task04( ) {
	char *domains[ ] = { "900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org" };

	vdvector_t subdomains = vdvector_create( 0u, sizeof( domain_info_t ) );
	task04( domains, 4u, &subdomains );

	
	for ( size_t i = 0u; i < subdomains.m_size; ++i ) {
		domain_info_t info;
		vdvector_get( &subdomains, i, &info );

		printf( "%d %s\n", info.m_visits, info.m_name );
	}

	printf( "task04 OK\n" );
}

void test_task05( ) {
	matrix_t mm0 = createMatrixFromArray( ( int[ ] ) { 1, 0, 1, 1, 1, 0, 1, 1, 0 }, 3, 3 );

	int ret0 = 0;
	task05( &mm0, &ret0 );

	assert( ret0 == 13 );

	matrix_t mm1 = createMatrixFromArray( ( int[ ] ) { 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 }, 3, 4 );
	int ret1 = 0;
	task05( &mm1, &ret1 );
	
	assert( ret1 == 24 );

	printf( "task05 OK\n" );
}

void test_task06( ) {
	char *sig0 = "IIIDIDDD";
	int   ret0;
	task06( sig0, &ret0 );

	assert( ret0 == 123549876 );

	char *sig1 = "DDD";
	int   ret1;
	task06( sig1, &ret1 );

	assert( ret1 == 4321 );

	printf( "task06 OK\n" );
}

enum RootState {
	ROOT_NULL,
};
void printLeftRight( node_t *left, node_t *right ) {
	int shouldnt_print_next_root = left == NULL && right == NULL;
	if ( shouldnt_print_next_root )
		return;

	if ( left )
		printf( "%d ", left->m_value );
	else
		printf( "(null) " );

	if ( right )
		printf( "%d ", right->m_value );
	else
		printf( "(null) " );
}

void printTree_( node_t *root ) {
	if ( root == NULL ) {
		return;
	}

	node_t *left = root->m_left, *right = root->m_right;
	if ( left || right ) {
		printLeftRight( left, right );
		if ( left )
			printLeftRight( left->m_left, left->m_right );
		if ( right )
			printLeftRight( right->m_left, right->m_right );

		if ( left ) {
			printTree_( left->m_left );
			printTree_( left->m_right );
		} 

		if ( right ) {
			printTree_( right->m_left );
			printTree_( right->m_right );
		}
	}
}

void printTree( node_t *tree ) {
	printf( "%d ", tree->m_value );
	printTree_( tree );
	printf( "\n" );
}

void test_task07( ) {
	int arr0[ ] = { 3, 2, 1, 6, 0, 5 };

	node_t *tree0 = task07( arr0, 6u );
	
	printf( "	tree0: " );
	printTree( tree0 );

	int arr1[ ] = { 3, 12, 6, 7, 8, 4, 1, 10 };
	
	node_t *tree1 = task07( arr1, 8u );

	printf( "	tree1: " );
	printTree( tree1 );

	printf( "task07 OK\n" );
}

void test_task08( ) {
	char *s0 = "abc";
	int indices0[ ] = { 0, 1, 2 };
	
	task08( s0, indices0 );
	ASSERT_STRING( "abc", s0 );

	char *s1 = "abap";
	int indices1[ ] = { 0, 3, 2, 1 };
	task08( s1, indices1 );

	ASSERT_STRING( "apab", s1 );
}

void test_task09( char **argv, int argc ) {
	gWriteLine( "data/20/task09i.txt", "9 2 4 1 0 15 21 45" );

	vdvector_t vec = vdvector_create( 0u, sizeof( int ) );
	task09( argv, argc, &vec );

	int assertion[ ] = {
		9, 4, 15, 21, 45
	};

	assert( vec.m_size == 5u );
	for ( size_t i = 0u; i < 5u; ++i ) {
		int x;
		vdvector_get( &vec, i, &x );
		assert( assertion[ i ] == x );
	}
}

void test_lab_content( char **argv, int argc ) {
	test_task01( );

	test_task02( );

	test_task03( );

	test_task04( );

	test_task05( );

	test_task06( );

	test_task07( );

	test_task08( );

	test_task09( argv, argc );
}