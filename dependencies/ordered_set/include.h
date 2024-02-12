#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef struct ordered_set {
	int *m_data;
	size_t  m_size;
	size_t  m_capacity;
} ordered_set_t;

ordered_set_t   ordered_set_create( const size_t capacity );

ordered_set_t   ordered_set_create_from_array( const int *array, const size_t size );

size_t			ordered_set_in( const ordered_set_t set, const int value );

size_t			ordered_set_isSubset( const ordered_set_t sub, const ordered_set_t parent );

int		 		ordered_set_isEqual( const ordered_set_t a, const ordered_set_t b );

void	 		ordered_set_isAbleToAppend( ordered_set_t *set );

void	 		ordered_set_insert( ordered_set_t *set, const int value );

void	 	  	ordered_set_delete( ordered_set_t *set, const int value );

ordered_set_t   ordered_set_union( const ordered_set_t a, const ordered_set_t b );

ordered_set_t   ordered_set_intersection( const ordered_set_t a, const ordered_set_t b );

ordered_set_t   ordered_set_diff( const ordered_set_t a, const ordered_set_t b );

ordered_set_t   ordered_set_symdiff( const ordered_set_t a, const ordered_set_t b );

ordered_set_t   ordered_set_complement( const ordered_set_t set, const ordered_set_t universum );

void			ordered_set_print( const ordered_set_t set );

void			ordered_set_erasemem( ordered_set_t *set );