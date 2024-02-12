#include "../include.h"

bset_t bset_create( const unsigned max_value ) {
	bset_t res;

	res.m_data = 0u; // zero data.
	res.m_max_value = max_value; // set max value in set.

	return res;
}

int	bset_in( const bset_t set, const unsigned value ) {
	if ( value > set.m_max_value )
		return 0;

	return ( set.m_data & ( 1 << value ) ) ? 1 : 0;
}

int bset_isEqual( const bset_t a, const bset_t b ) {
	if ( a.m_max_value != b.m_max_value )
		return 0;

	return a.m_data == b.m_data;
}

int bset_isSubset( const bset_t sub, const bset_t parent ) {
	if ( sub.m_data > parent.m_data
		|| sub.m_max_value > parent.m_max_value )
		return 0;

	for ( size_t i = 0u; i <= sub.m_max_value; ++i ) {
		int a = bset_in( parent, i );
		int b = bset_in( sub, i );
		if ( b && a != b )
			return 0;
	}

	return 1;
}

void bset_insert( bset_t *set, const unsigned value ) {
	assert( set && set->m_max_value >= value );

	set->m_data |= ( 1 << value );
}

void bset_delete( bset_t *set, const unsigned value ) {
	assert( set && set->m_max_value >= value );
	if ( bset_in( *set, value ) )
		set->m_data &= ~( 1 << value );
}

bset_t bset_union( const bset_t a, const bset_t b ) {
	size_t max_value = a.m_max_value > b.m_max_value
		? a.m_max_value : b.m_max_value;

	bset_t res = bset_create( max_value );

	for ( size_t i = 0u; i < max_value; ++i )
		if ( bset_in( a, i ) || bset_in( b, i ) )
			bset_insert( &res, i );

	return res;
}

bset_t bset_intersection( const bset_t a, const bset_t b ) {
	size_t max_value = a.m_max_value > b.m_max_value
		? a.m_max_value : b.m_max_value;

	bset_t res = bset_create( max_value );

	for ( size_t i = 0u; i < max_value; ++i )
		if ( bset_in( a, i ) && bset_in( b, i ) )
			bset_insert( &res, i );

	return res;
}

bset_t bset_diff( const bset_t a, const bset_t b ) {
	size_t max_value = a.m_max_value > b.m_max_value
		? a.m_max_value : b.m_max_value;

	bset_t res = bset_create( max_value );

	for ( size_t i = 0u; i < max_value; ++i )
		if ( bset_in( a, i ) && !bset_in( b, i ) )
			bset_insert( &res, i );

	return res;
}

bset_t bset_symdiff( const bset_t a, const bset_t b ) {
	size_t max_value = a.m_max_value > b.m_max_value
		? a.m_max_value : b.m_max_value;

	bset_t res = bset_create( max_value );

	for ( size_t i = 0u; i < max_value; ++i )
		if ( ( bset_in( a, i ) && !bset_in( b, i ) )
			|| ( !bset_in( a, i ) && bset_in( b, i ) ) )
			bset_insert( &res, i );

	return res;
}

bset_t bset_complement( const bset_t set ) {
	bset_t res = bset_create( set.m_max_value );

	for ( size_t i = 0u; i < res.m_max_value; ++i ) {
		if ( !bset_in( set, i ) )
			bset_insert( &res, i );
	}

	return res;
}