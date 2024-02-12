#include "../include.h"

#include <ordered_set/include.h>

// additional methods.
static void unordered_set_shrink_to_fit( unordered_set_t *set ) {
	if ( set->m_capacity != set->m_size ) {
		set->m_data = realloc( set->m_data, sizeof( int ) * set->m_size );
		set->m_capacity = set->m_size;
	}
}

unordered_set_t unordered_set_create( const size_t capacity ) {
	unordered_set_t res;

	res.m_size = 0u;
	res.m_capacity = capacity;
	res.m_data = malloc( sizeof( int ) * capacity );

	return res;
}

unordered_set_t unordered_set_create_from_array( const int *array, const size_t size ) {
	unordered_set_t set = unordered_set_create( size );

	for ( size_t i = 0u; i < size; ++i )
		unordered_set_insert( &set, array[ i ] );

	unordered_set_shrink_to_fit( &set );

	return set;
}

size_t unordered_set_in( const unordered_set_t set, const int value ) {
	for ( size_t i = 0u; i < set.m_size; ++i )
		if ( set.m_data[ i ] == value )
			return i;

	return set.m_size;
}

size_t unordered_set_isSubset( const unordered_set_t sub, const unordered_set_t parent ) {
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

int unordered_set_isEqual( const unordered_set_t a, const unordered_set_t b ) {
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

void unordered_set_isAbleToAppend( unordered_set_t *set ) {
	assert( set->m_size < set->m_capacity );
}

void unordered_set_insert( unordered_set_t *set, const int value ) {
	if ( unordered_set_in( *set, value ) == set->m_size ) {
		unordered_set_isAbleToAppend( set );

		/* we shouldn`t resize set cuz ^^^
		if ( set->m_size + 1 > set->m_capacity ) {
			set->m_capacity *= 2u;
			set->m_data = realloc( set->m_data, sizeof( int ) * set->m_capacity );
		}*/

		set->m_data[ set->m_size++ ] = value;
	}
}

void unordered_set_delete( unordered_set_t *set, const int value ) {
	if ( unordered_set_in( *set, value ) == set->m_size )
		return;

	size_t read = 0u;
	while ( read < set->m_size ) {
		if ( set->m_data[ read ] == value )
			set->m_data[ read ] = set->m_data[ --set->m_size ];
		else
			++read;
	}
}

unordered_set_t unordered_set_union( const unordered_set_t a, const unordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	unordered_set_t set = unordered_set_create( estimate_capacity );
	
	// add set(a) values.
	for ( size_t i = 0u; i < a.m_size; ++i ) {
		unordered_set_insert( &set, a.m_data[ i ] );
	}

	// add set(b) values.
	for ( size_t i = 0u; i < b.m_size; ++i ) {
		unordered_set_insert( &set, b.m_data[ i ] );
	}

	unordered_set_shrink_to_fit( &set );

	return set;
}

unordered_set_t unordered_set_intersection( const unordered_set_t a, const unordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	unordered_set_t set = unordered_set_create( estimate_capacity );

	for ( size_t i = 0u; i < a.m_size; ++i ) {
		for ( size_t j = 0u; j < b.m_size; ++j ) {
			if ( a.m_data[ i ] == b.m_data[ j ] )
				unordered_set_insert( &set, a.m_data[ i ] );
		}
	}

	unordered_set_shrink_to_fit( &set );

	return set;
}

unordered_set_t unordered_set_diff( const unordered_set_t a, const unordered_set_t b ) {
	size_t estimate_capacity = a.m_size + b.m_size;

	unordered_set_t set = unordered_set_create( estimate_capacity );

	for ( size_t i = 0u; i < a.m_size; ++i ) {
		int should_insert = 1;
		for ( size_t j = 0u; j < b.m_size; ++j ) {
			if ( a.m_data[ i ] == b.m_data[ j ] )
				should_insert = 0;
		}

		if ( should_insert )
				unordered_set_insert( &set, a.m_data[ i ] );
	}

	unordered_set_shrink_to_fit( &set );

	return set;
}

unordered_set_t unordered_set_symdiff( const unordered_set_t a, const unordered_set_t b ) {
	unordered_set_t left  = unordered_set_diff( a, b );
	unordered_set_t right = unordered_set_diff( b, a );
	
	unordered_set_t set = unordered_set_union( left, right );

	unordered_set_shrink_to_fit( &set );

	return set;
}

unordered_set_t unordered_set_complement( const unordered_set_t set, const unordered_set_t universum ) {
	unordered_set_t diff = unordered_set_diff( universum, set );

	return diff;
	/*
	unordered_set_t res = unordered_set_create( universum.m_size );

	for ( size_t i = 0u; i < universum.m_size; ++i ) {
		int is_in_universum = 0;
		for ( size_t j = 0u; j < set.m_size; ++j ) {
			if ( set.m_data[ j ] == universum.m_data[ i ] ) {
				is_in_universum = 1;
				break;
			}
		}

		if ( !is_in_universum )
			unordered_set_insert( &res, universum.m_data[ i ] );
	}

	unordered_set_shrink_to_fit( &res );

	return res;*/
}

void unordered_set_print( const unordered_set_t set ) {
	for ( size_t i = 0u; i < set.m_size; ++i )
		printf( "%d ", set.m_data[ i ] );

	printf( "\n" );
}

void unordered_set_erasemem( unordered_set_t *set ) {
	set->m_capacity = 0u;
	set->m_size = 0u;
	free( set->m_data );
}