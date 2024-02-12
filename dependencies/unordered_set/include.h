#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef struct unordered_set {
	int		*m_data;
	size_t  m_size;
	size_t  m_capacity;
} unordered_set_t;

unordered_set_t  unordered_set_create( const size_t capacity );

unordered_set_t  unordered_set_create_from_array( const int *array, const size_t size );

size_t			 unordered_set_in( const unordered_set_t set, const int value );

size_t			 unordered_set_isSubset( const unordered_set_t sub, const unordered_set_t parent );

int		 		 unordered_set_isEqual( const unordered_set_t a, const unordered_set_t b );

void	 		 unordered_set_isAbleToAppend( unordered_set_t *set );

void	 		 unordered_set_insert( unordered_set_t *set, const int value );

void	 	  	 unordered_set_delete( unordered_set_t *set, const int value );

unordered_set_t  unordered_set_union( const unordered_set_t a, const unordered_set_t b );

unordered_set_t  unordered_set_intersection( const unordered_set_t a, const unordered_set_t b );

unordered_set_t  unordered_set_diff( const unordered_set_t a, const unordered_set_t b );

unordered_set_t  unordered_set_symdiff( const unordered_set_t a, const unordered_set_t b );

unordered_set_t  unordered_set_complement( const unordered_set_t set, const unordered_set_t universum );

void			 unordered_set_print( const unordered_set_t set );

void			 unordered_set_erasemem( unordered_set_t *set );