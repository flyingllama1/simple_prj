#include <malloc.h>
#include <assert.h>

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

int		*vector_at( vector_t *vec, const size_t slot );

int		*vector_back( vector_t *vec );

int		*vector_front( vector_t *vec );