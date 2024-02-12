#include "../include.h"

#include <vector/include.h>

#include <vdvector/include.h>

void test_vector_content0( ) {
	vector_t vec = vector_create( 0u );
	assert( vec.m_data == NULL );

	vec = vector_create( 1u );
	assert( vec.m_capacity == 1u );
	
	vector_reverse( &vec, 2u );
	assert( vec.m_capacity == 2u );

	vec.m_size = 1u;
	vector_clear( &vec );
	assert( vec.m_size == 0u );
	assert( vec.m_data != NULL );

	vector_reverse( &vec, 4u );
	assert( vec.m_capacity == 4u );

	vec.m_size = 2u;
	vector_shrinkToFit( &vec );
	assert( vec.m_capacity == 2u );

	vector_free( &vec );
	assert( vec.m_data == NULL );
}

void test_pushBack_emptyVector( ) {
	vector_t a = vector_create( 0u );
	assert( a.m_capacity == 0u );

	vector_pushBack( &a, 1 );
	assert( a.m_capacity == 1u );
}

void test_pushBack_fullVector( ) {
	vector_t a = vector_create( 1u );
	vector_pushBack( &a, 1 );
	vector_pushBack( &a, 2 );
	assert( a.m_capacity == 2u );

	vector_pushBack( &a, 3 );

	assert( a.m_capacity == 4u );
	vector_pushBack( &a, 4 );
	vector_pushBack( &a, 5 );

	assert( a.m_capacity == 8u );
}

void test_popBack_nonEmptyVector( ) {
	vector_t a = vector_create( 0u );
	vector_pushBack( &a, 1 );
	assert( a.m_size == 1 );
	vector_popBack( &a );
	assert( a.m_size == 0 );
	assert( a.m_capacity == 1 );
}

void test_vector_memory( ) {
	vector_t a = vector_create( 3u );

	vector_pushBack( &a, 1 );
	assert( *vector_front( &a ) == 1
		&& *vector_back( &a ) == 1
		&& *vector_at( &a, 0u ) == 1
	);

	vector_pushBack( &a, 2 );
	vector_pushBack( &a, 3 );
	assert( 
		vector_get( a, 0u ) == 1 
		&& vector_get( a, 1u ) == 2 
		&& vector_get( a, 2u ) == 3 
	);

	*vector_back( &a ) = 1337;
	*vector_front( &a ) = 123;
	*vector_at( &a, 1u ) = 0xDEAD;
	assert( 
		vector_get( a, 0u ) == 123 
		&& vector_get( a, 1u ) == 0xDEAD
		&& vector_get( a, 2u ) == 1337
	);
}

void test_vector_content1( ) {
	test_pushBack_emptyVector( );
	test_pushBack_fullVector( );
	test_popBack_nonEmptyVector( );
	test_vector_memory( );
}

void test_vdvector_content0( ) {
	vdvector_t vec = vdvector_create( 0u, sizeof( int ) );
	assert( vec.m_data == NULL );
	assert( vec.m_base_type_size == sizeof( int ) );

	vec = vdvector_create( 1u, sizeof( short ) );
	assert( vec.m_capacity == 1u );
	assert( vec.m_base_type_size == sizeof( short ) );

	vdvector_reverse( &vec, 2u );
	assert( vec.m_capacity == 2u );

	vec.m_size = 1u;
	vdvector_clear( &vec );
	assert( vec.m_size == 0u );
	assert( vec.m_data != NULL );

	vdvector_reverse( &vec, 4u );
	assert( vec.m_capacity == 4u );

	vec.m_size = 2u;
	vdvector_shrinkToFit( &vec );
	assert( vec.m_capacity == 2u );

	vdvector_free( &vec );
	assert( vec.m_data == NULL );

	vec = vdvector_create( 2u, sizeof( short ) );
	short a = 2;
	short b = 4;
	vdvector_pushBack( &vec, &a );
	vdvector_pushBack( &vec, &b );
	assert( vdvector_isEmpty( vec ) == 0 );
	assert( vdvector_isFull( vec ) == 1 );

	short resa, resb;
	vdvector_get( &vec, 0, &resa );
	vdvector_get( &vec, 1, &resb );
	assert(
		resa == a && resb == b
	);

	vdvector_clear( &vec );
	assert( vdvector_isEmpty( vec ) == 1 );
	assert( vdvector_isFull( vec ) == 0 );

	vdvector_pushBack( &vec, &a );
	vdvector_popBack( &vec );
	assert( vdvector_isEmpty( vec ) == 1 );

	vdvector_pushBack( &vec, &a );
	vdvector_set( &vec, 0, &b );

	short resc;
	vdvector_get( &vec, 0, &resc );
	assert( resc == b );
}