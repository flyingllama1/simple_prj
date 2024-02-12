#include "../include.h"

#include <algorithm/include.h>

static void ordered_set_shrink_to_fit( ordered_set_t *set ) {
	if ( set->m_capacity != set->m_size ) {
		set->m_data = realloc( set->m_data, sizeof( int ) * set->m_size );
		set->m_capacity = set->m_size;
	}
}

ordered_set_t ordered_set_create( const size_t capacity ) {
	ordered_set_t res;

	res.m_size = 0u;
	res.m_capacity = capacity;
	res.m_data = malloc( sizeof( int ) * capacity );

	return res;
}

ordered_set_t ordered_set_create_from_array( const int *array, const size_t size ) {
	ordered_set_t set = ordered_set_create( size );
	int *c = malloc( -1 );
	for ( size_t i = 0u; i < size; ++i )
		ordered_set_insert( &set, array[ i ] );

	ordered_set_shrink_to_fit( &set );

	return set;
}

size_t ordered_set_in( const ordered_set_t set, const int value ) {
	return binsrch( set.m_data, set.m_size, value );
}

size_t ordered_set_isSubset( const ordered_set_t sub, const ordered_set_t parent ) {
	if ( sub.m_size > parent.m_size )
		return 0;

	size_t intersections = 0u;
	for ( size_t i = 0u; i < parent.m_size; ++i ) {
		for ( size_t j = 0u; j < sub.m_size; ++j ) {
			if ( sub.m_data[ j ] == parent.m_data[ i + j ] )
				++intersections;
			else {
				intersections = 0;
				break;
			}

			if ( intersections == sub.m_size )
				return i;
		}
	}

	return parent.m_size;
}

int	ordered_set_isEqual( const ordered_set_t a, const ordered_set_t b ) {
	if ( a.m_size != b.m_size )
		return 0;

	size_t intersections = 0u;
	for ( size_t i = 0u; i < a.m_size; ++i ) {
		for ( size_t j = 0u; j < b.m_size; ++j ) {
			if ( a.m_data[ i ] == b.m_data[ j ] )
				++intersections;

		}
	}

	if ( intersections == a.m_size )
		return 1;

	return 0;
}

void ordered_set_isAbleToAppend( ordered_set_t *set ) {
	assert( set->m_size < set->m_capacity );
}

void ordered_set_insert( ordered_set_t *set, const int value ) {
	if ( ordered_set_in( *set, value ) == set->m_size ) {
		ordered_set_isAbleToAppend( set );

		if ( set->m_size - 1 >= set->m_capacity ) {
			set->m_data[ set->m_size++ ] = value;
		}
		else {
			size_t req_pos = binsrch_me( set->m_data, set->m_size, value );

			for ( size_t i = set->m_size; i > req_pos; --i )
				set->m_data[ i ] = set->m_data[ i - 1 ];

			set->m_data[ req_pos ] = value;
			++set->m_size;
		}
	}
}

void ordered_set_delete( ordered_set_t *set, const int value ) {
	if ( ordered_set_in( *set, value ) == set->m_size )
		return;

	size_t read = 0u;
	while ( read < set->m_size && set->m_data[ read ] != value )
		++read;

	size_t write = read;
	while ( read < set->m_size ) {
		if ( set->m_data[ read ] != value )
			set->m_data[ write++ ] = set->m_data[ read ];

		++read;
	}

	set->m_size = write;
}

ordered_set_t ordered_set_union( const ordered_set_t a, const ordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	ordered_set_t set = ordered_set_create( estimate_capacity );

	// add set(a) values.
	for ( size_t i = 0u; i < a.m_size; ++i ) {
		ordered_set_insert( &set, a.m_data[ i ] );
	}

	// add set(b) values.
	for ( size_t i = 0u; i < b.m_size; ++i ) {
		ordered_set_insert( &set, b.m_data[ i ] );
	}

	ordered_set_shrink_to_fit( &set );

	return set;
}

ordered_set_t ordered_set_intersection( const ordered_set_t a, const ordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	ordered_set_t set = ordered_set_create( estimate_capacity );

	ordered_set_t parent = a;
	ordered_set_t sub = b;
	if ( b.m_size > a.m_size )
		swap( ( void* )&a, ( void* )&b );

	for ( size_t i = 0u; i < parent.m_size; ++i ) {
		size_t slot = binsrch( sub.m_data, sub.m_size, parent.m_data[ i ] );

		if ( slot != sub.m_size )
			ordered_set_insert( &set, parent.m_data[ i ] );
	}

	ordered_set_shrink_to_fit( &set );

	return set;
}

ordered_set_t ordered_set_diff( const ordered_set_t a, const ordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	ordered_set_t set = ordered_set_create( estimate_capacity );

	ordered_set_t parent = a;
	ordered_set_t sub = b;
	if ( b.m_size > a.m_size )
		swap( ( void* )&a, ( void* )&b );

	for ( size_t i = 0u; i < parent.m_size; ++i ) {
		size_t slot = binsrch( sub.m_data, sub.m_size, parent.m_data[ i ] );

		if ( slot == sub.m_size )
			ordered_set_insert( &set, parent.m_data[ i ] );
	}

	ordered_set_shrink_to_fit( &set );

	return set;
}

ordered_set_t ordered_set_symdiff( const ordered_set_t a, const ordered_set_t b ) {
	ordered_set_t left = ordered_set_diff( a, b );
	ordered_set_t right = ordered_set_diff( b, a );

	ordered_set_t set = ordered_set_union( left, right );

	return set;
}

ordered_set_t ordered_set_complement( const ordered_set_t set, const ordered_set_t universum ) {
	ordered_set_t diff = ordered_set_diff( universum, set );

	return diff;
}

void ordered_set_print( const ordered_set_t set ) {
	for ( size_t i = 0u; i < set.m_size; ++i )
		printf( "%d ", set.m_data[ i ] );
	printf( "\n" );
}

void ordered_set_erasemem( ordered_set_t *set ) {
	set->m_size = 0u;
	set->m_capacity = 0u;
	free( set->m_data );
}