#include "../include.h"

#include <stdio.h>
#include <stdlib.h>

vector_t vector_create( const size_t size ) {
	vector_t vec;

	if ( size == 0 ) {
		vec.m_data = NULL;
	}
	else {
		vec.m_data = malloc( sizeof( int ) * size );
		if ( !vec.m_data ) {
			fprintf( stderr, "0x%p: %s > bad alloc", &vector_create, ERR_GET_FN_NAME( vector_create ) );
			exit( 1 );
		}
	}

	vec.m_size = 0u;
	vec.m_capacity = size;

	return vec;
}

void vector_reverse( vector_t *vec, const size_t new_capacity ) {
	if ( new_capacity == 0 ) {
		vector_free( vec );
	}
	else {
		if ( vec->m_size > new_capacity )
			vec->m_size = new_capacity;

		vec->m_capacity = new_capacity;
		vec->m_data = realloc( vec->m_data, sizeof( int ) * vec->m_capacity );
		if ( !vec->m_data ) {
			fprintf( stderr, "0x%p: %s > bad realloc", &vector_reverse, ERR_GET_FN_NAME( vector_reverse ) );
			exit( 1 );
		}
	}
}

void vector_clear( vector_t *vec ) {
	vec->m_size = 0u;
}

void vector_shrinkToFit( vector_t *vec ) {
	vector_reverse( vec, vec->m_size );
}

void vector_free( vector_t *vec ) {
	if ( vec->m_data )
		free( vec->m_data );

	vec->m_size = 0u;
	vec->m_capacity = 0u;
	vec->m_data = NULL;
}