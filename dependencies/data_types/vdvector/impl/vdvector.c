#include "../include.h"

#include <exceptions/include.h>

#include <memory.h>

vdvector_t vdvector_create( const size_t size, const size_t type_size ) {
	vdvector_t vec;

	if ( size == 0 ) {
		vec.m_data = NULL;
	}
	else {
		vec.m_data = malloc( type_size * size );
		if ( !vec.m_data ) {
			STD_ERROR_N_EXIT( vdvector_create, "bad allocation for vec.m_data{}" );
		}
	}

	vec.m_size = 0u;
	vec.m_capacity = size;
	vec.m_base_type_size = type_size;

	return vec;
}

void vdvector_reverse( vdvector_t *vec, const size_t new_capacity ) {
	if ( new_capacity == 0 ) {
		vector_free( vec );
	}
	else {
		if ( vec->m_size > new_capacity )
			vec->m_size = new_capacity;

		vec->m_capacity = new_capacity;
		vec->m_data = realloc( vec->m_data, vec->m_base_type_size * vec->m_capacity );
		if ( !vec->m_data ) {
			STD_ERROR_N_EXIT( vdvector_reverse, "bad reallocation for vec.m_data{}" );
		}
	}
}

void vdvector_clear( vdvector_t *vec ) {
	vec->m_size = 0u;
}

void vdvector_shrinkToFit( vdvector_t *vec ) {
	vdvector_reverse( vec, vec->m_size );
}

void vdvector_free( vdvector_t *vec ) {
	if ( vec->m_data )
		free( vec->m_data );

	vec->m_size = 0u;
	vec->m_capacity = 0u;
	vec->m_base_type_size = 0u;
	vec->m_data = NULL;
}

int	vdvector_isEmpty( const vdvector_t vec ) {
	return vec.m_size == 0u;
}

int	vdvector_isFull( const vdvector_t vec ) {
	return vec.m_size == vec.m_capacity;
}

void vdvector_get( vdvector_t *vec, const size_t slot, void *dst ) {
	if ( !vec->m_data ) {
		STD_ERROR_N_EXIT( vdvector_get, "failed access to vdvector`s memory" );
	}

	if ( slot >= vec->m_size ) {
		STD_ERROR_N_EXIT( vdvector_get, "index is out of vdvector`s range" );
	}

	char *src = ( char * )vec->m_data + slot * vec->m_base_type_size;
	memcpy( dst, src, vec->m_base_type_size );
}

void vdvector_set( vdvector_t *vec, const size_t slot, void *src ) {
	if ( !vec->m_data ) {
		STD_ERROR_N_EXIT( vdvector_get, "failed access to vdvector`s memory" );
	}

	if ( slot >= vec->m_size ) {
		STD_ERROR_N_EXIT( vdvector_set, "index is out of vdvector`s range" );
	}

	char *dst = ( char * )vec->m_data + slot * vec->m_base_type_size;
	memcpy( dst, src, vec->m_base_type_size );
}

void vdvector_pushBack( vdvector_t *vec, void *src ) {
	if ( !vec->m_capacity )
		vdvector_reverse( vec, 1u );

	if ( vec->m_size >= vec->m_capacity )
		vdvector_reverse( vec, vec->m_capacity * 2u );

	vdvector_set( vec, vec->m_size++, src );
}

void vdvector_popBack( vdvector_t *vec ) {
	if ( !vec->m_data ) {
		STD_ERROR_N_EXIT( vdvector_get, "failed access to vdvector`s memory" );
	}

	if ( !vec->m_size ) {
		STD_ERROR( vdvector_popBack, "vdvector is empty" );
	}

	--vec->m_size;
}