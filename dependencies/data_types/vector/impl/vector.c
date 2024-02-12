#include "../include.h"

#include <stdio.h>
#include <stdlib.h>

#include <exceptions/include.h>

vector_t vector_create( const size_t size ) {
	vector_t vec;

	if ( size == 0 ) {
		vec.m_data = NULL;
	}
	else {
		vec.m_data = malloc( sizeof( int ) * size );
		if ( !vec.m_data ) {
			STD_ERROR_N_EXIT( vector_create, "bad allocation for vec.m_data{}" );
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
			STD_ERROR_N_EXIT( vector_reverse, "bad reallocation for vec.m_data{}" );
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

int	vector_isEmpty( const vector_t vec ) {
	return vec.m_size == 0u;
}

int	vector_isFull( const vector_t vec ) {
	return vec.m_size == vec.m_capacity;
}

int vector_get( const vector_t vec, const size_t slot ) {
	if ( !vec.m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	if ( slot >= vec.m_size ) {
		STD_ERROR_N_EXIT( vector_get, "index is out of vector range" );
	}

	return vec.m_data[ slot ];
}

void vector_pushBack( vector_t *vec, const int value ) {
	if ( !vec->m_capacity )
		vector_reverse( vec, 1u );

	if ( vec->m_size >= vec->m_capacity )
		vector_reverse( vec, vec->m_capacity * 2u );

	vec->m_data[ vec->m_size++ ] = value;
}

void vector_popBack( vector_t *vec ) {
	if ( !vec->m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	if ( !vec->m_size ) {
		STD_ERROR( vector_popBack, "vector empty" );
	}

	vec->m_data[ vec->m_size-- ] = 0;
}

int *vector_at( vector_t *vec, const size_t slot ) {
	if ( !vec->m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	if ( slot >= vec->m_size ) {
		STD_ERROR_N_EXIT( vector_at, "index is out of vector range" );
	}

	return vec->m_data + slot;
}

int *vector_back( vector_t *vec ) {
	if ( !vec->m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	return vec->m_data + ( vec->m_size - 1 );
}

int *vector_front( vector_t *vec ) {
	if ( !vec->m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	return vec->m_data;
}

void vector_print( const vector_t vec ) {
	if ( !vec.m_data )
		STD_ERROR_N_EXIT( vector_get, "failed access to vector`s memory" );

	printf( "{ %d: ", vec.m_capacity );
	for ( size_t i = 0u; i < vec.m_size; ++i )
		printf( "%d ", vec.m_data[ i ] );
	printf( "}\n" );
}