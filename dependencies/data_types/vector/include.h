#include <malloc.h>
#include <assert.h>

#define ERR_GET_FN_NAME(fn) (#fn)
#define STD_ERROR(fn, err) \
	fprintf(stderr, "0x%p: %s -> %s.\n", &fn, ERR_GET_FN_NAME(fn), err)

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

int		 vector_isEmpty( const vector_t vec );

int		 vector_isFull( const vector_t vec );

int		 vector_get( const vector_t vec, const size_t slot );

void	 vector_pushBack( vector_t *vec, const int value );

void	 vector_popBack( vector_t *vec );

void     vector_print( const vector_t vec );