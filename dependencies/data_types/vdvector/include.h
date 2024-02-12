#include <malloc.h>
#include <assert.h>

typedef struct vdvector {
	int		*m_data;
	size_t   m_size;
	size_t   m_capacity;
	size_t	 m_base_type_size;
} vdvector_t;

vdvector_t  vdvector_create( const size_t size, const size_t type_size );

void		vdvector_reverse( vdvector_t *vec, const size_t new_capacity );

void		vdvector_clear( vdvector_t *vec );

void		vdvector_shrinkToFit( vdvector_t *vec );

void		vdvector_free( vdvector_t *vec );