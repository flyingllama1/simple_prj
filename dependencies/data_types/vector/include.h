#include <malloc.h>
#include <assert.h>

#define ERR_GET_FN_NAME(fn) #fn

typedef struct vector {
	int    *m_data;
	size_t  m_size;
	size_t  m_capacity;
} vector_t;

vector_t vector_create( const size_t size );

void	 vector_reverse( vector_t *vec, const size_t new_capacity );

void	 vector_clear( vector_t *vec );

void	 vector_shrinkToFit( vector_t *vec );

void	 vector_free( vector_t *vec );