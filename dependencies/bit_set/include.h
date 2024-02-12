#include <assert.h>

typedef struct bset {
	unsigned m_data;
	unsigned m_max_value;
} bset_t;

bset_t	bset_create( const unsigned max_value );

int		bset_in( const bset_t set, const unsigned value );

int		bset_isEqual( const bset_t a, const bset_t b );

int		bset_isSubset( const bset_t sub, const bset_t parent );

void	bset_insert( bset_t *set, const unsigned value );

void	bset_delete( bset_t *set, const unsigned value );

bset_t	bset_union( const bset_t a, const bset_t b );

bset_t	bset_intersection( const bset_t a, const bset_t b );

bset_t	bset_diff( const bset_t a, const bset_t b );

bset_t	bset_symdiff( const bset_t a, const bset_t b );

bset_t	bset_complement( const bset_t set );