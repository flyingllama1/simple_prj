#include "../include.h"

#include <vector/include.h>

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