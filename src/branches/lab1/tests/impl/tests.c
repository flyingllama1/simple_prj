#include "../include.h"

#include <bit_set/include.h>

#include <unordered_set/include.h>

#include <ordered_set/include.h>

bset_t bset_a, bset_b, bset_c;

void test_init_bsets( ) {
	bset_a = bset_create( 10 );
	bset_b = bset_create( 6 );
	bset_c = bset_create( 6 );

	bset_insert( &bset_a, 1 );
	bset_insert( &bset_a, 3 );
	bset_insert( &bset_a, 5 );
	bset_insert( &bset_a, 7 );

	bset_insert( &bset_b, 3 );
	bset_insert( &bset_b, 5 );
	bset_insert( &bset_b, 6 );

	bset_insert( &bset_c, 3 );
	bset_insert( &bset_c, 5 );
}
void test_bset( ) {
	test_init_bsets( );

	test_bset_in( );

	test_bset_isEqual( );

	test_bset_in( );

	test_bset_isSubset( );

	test_bset_insert( );

	test_bset_delete( );

	test_bset_union( );

	test_bset_intersection( );

	test_bset_diff( );

	test_bset_symdiff( );

	test_bset_complement( );
}

void test_bset_in( ) {
	const int value = 3;

	assert( bset_in( bset_a, 3 ) );
	assert( bset_in( bset_a, 1 ) );
	assert( bset_in( bset_a, 5 ) );
	assert( bset_in( bset_a, 7 ) );
	assert( !bset_in( bset_a, 2 ) );
}

void test_bset_isEqual( ) {
	assert( !bset_isEqual( bset_a, bset_b ) );
}

void test_bset_isSubset( ) {
	assert( !bset_isSubset( bset_b, bset_a ) );
	assert( bset_isSubset( bset_c, bset_a ) );
}

void test_bset_insert( ) {
	bset_t t = bset_create( 6 );

	bset_insert( &t, 3 );
	bset_insert( &t, 5 );

	assert( bset_isEqual( bset_c, t ) );
}

void test_bset_delete( ) {
	bset_t t = bset_create( 6 );

	bset_insert( &t, 3 );
	bset_insert( &t, 5 );
	bset_insert( &t, 6 );

	bset_delete( &t, 6 );

	assert( bset_isEqual( bset_c, t ) );
}

void test_bset_union( ) {
	bset_t res = bset_create( 10 );
	bset_insert( &res, 1 );
	bset_insert( &res, 3 );
	bset_insert( &res, 5 );
	bset_insert( &res, 6 );
	bset_insert( &res, 7 );

	assert( bset_isEqual( res, bset_union( bset_a, bset_b ) ) );
}

void test_bset_intersection( ) {
	bset_t res = bset_create( 10 );
	bset_insert( &res, 3 );
	bset_insert( &res, 5 );

	assert( bset_isEqual( res, bset_intersection( bset_a, bset_b ) ) );
}

void test_bset_diff( ) {
	bset_t res = bset_create( 10 );
	bset_insert( &res, 1 );
	bset_insert( &res, 7 );

	assert( bset_isEqual( res, bset_diff( bset_a, bset_b ) ) );
}

void test_bset_symdiff( ) {
	bset_t res = bset_create( 10 );
	bset_insert( &res, 1 );
	bset_insert( &res, 6 );
	bset_insert( &res, 7 );

	assert( bset_isEqual( res, bset_symdiff( bset_a, bset_b ) ) );
}

void test_bset_complement( ) {
	bset_t res = bset_create( 6 );
	bset_insert( &res, 0 );
	bset_insert( &res, 1 );
	bset_insert( &res, 2 );
	bset_insert( &res, 4 );

	assert( bset_isEqual( res, bset_complement( bset_b ) ) );

	bset_delete( &res, 0 );

	assert( !bset_isEqual( res, bset_complement( bset_b ) ) );
}

unordered_set_t uset_a, uset_b, uset_c;

void test_init_usets( ) {
	uset_a = unordered_set_create_from_array( ( int[ ] ) { 3, 7, 5, 1 }, 4u );
	uset_b = unordered_set_create_from_array( ( int[ ] ) { 5, 6, 3 }, 3u );
}

void test_unordered_set( ) {
	test_unordered_set_create_from_array( );

	test_unordered_set_in( );

	test_unordered_set_isSubset( );

	test_unordered_set_isEqual( );

	test_unordered_set_insert( );

	test_unordered_set_delete( );

	test_unordered_set_union( );

	test_unordered_set_intersection( );

	test_unordered_set_diff( );

	test_unordered_set_symdiff( );

	test_unordered_set_complement( );
}

void test_unordered_set_create_from_array( ) {
	test_init_usets( );

	unordered_set_t res1 = unordered_set_create( 4u );
	unordered_set_t res2 = unordered_set_create( 4u );

	unordered_set_insert( &res1, 1 );
	unordered_set_insert( &res1, 3 );
	unordered_set_insert( &res1, 5 );
	unordered_set_insert( &res1, 7 );

	unordered_set_insert( &res2, 6 );
	unordered_set_insert( &res2, 3 );
	unordered_set_insert( &res2, 5 );

	assert( unordered_set_isEqual( uset_a, res1 ) );
	assert( unordered_set_isEqual( uset_b, res2 ) );
}

void test_unordered_set_in( ) {
	assert( unordered_set_in( uset_a, 1 ) == 3u );
	assert( unordered_set_in( uset_a, 8 ) == uset_a.m_size );
}

void test_unordered_set_isSubset( ) {
	unordered_set_t sub = unordered_set_create_from_array( ( int[ ] ) { 7, 5 }, 2u );

	assert( unordered_set_isSubset( sub, uset_a ) != uset_a.m_size );
	assert( unordered_set_isSubset( sub, uset_b ) == uset_b.m_size );
}

void test_unordered_set_isEqual( ) {
	unordered_set_t res1 = unordered_set_create( 4u );

	unordered_set_insert( &res1, 1 );
	unordered_set_insert( &res1, 3 );
	unordered_set_insert( &res1, 5 );
	unordered_set_insert( &res1, 7 );

	assert( unordered_set_isEqual( res1, uset_a ) );
	assert( !unordered_set_isEqual( uset_b, uset_a ) );
}

void test_unordered_set_insert( ) {
	unordered_set_t ab = unordered_set_create( 2 );
	unordered_set_insert( &ab, 1337 );

	assert( unordered_set_in( ab, 1337 ) == 0u );
}

void test_unordered_set_delete( ) {
	unordered_set_t ab = unordered_set_create( 2 );
	unordered_set_insert( &ab, 1337 );
	unordered_set_insert( &ab, 228 );

	unordered_set_delete( &ab, 1337 );

	assert( unordered_set_in( ab, 228 ) == 0u );
	assert( unordered_set_in( ab, 1337 ) == ab.m_size );
}
void test_unordered_set_union( ) {
	unordered_set_t res = unordered_set_union( uset_a, uset_b );
	unordered_set_t exp = unordered_set_create_from_array( ( int[ ] ) { 1, 3, 5, 6, 7 }, 5u );

	assert( unordered_set_isEqual( res, exp ) );
}
void test_unordered_set_intersection( ) {
	unordered_set_t res = unordered_set_intersection( uset_a, uset_b );
	unordered_set_t exp = unordered_set_create_from_array( ( int[ ] ) { 5, 3 }, 2u );

	assert( unordered_set_isEqual( res, exp ) );
}

void test_unordered_set_diff( ) {
	unordered_set_t res = unordered_set_diff( uset_a, uset_b );
	unordered_set_t exp = unordered_set_create_from_array( ( int[ ] ) { 1, 7 }, 2u );

	assert( unordered_set_isEqual( res, exp ) );
}

void test_unordered_set_symdiff( ) {
	unordered_set_t res = unordered_set_symdiff( uset_a, uset_b );
	unordered_set_t exp = unordered_set_create_from_array( ( int[ ] ) { 1, 7, 6 }, 3u );

	assert( unordered_set_isEqual( res, exp ) );
}

void test_unordered_set_complement( ) {
	unordered_set_t uni = unordered_set_create_from_array( ( int[ ] ) { 8, 5, 3, 4, 6, 1, 2, 7 }, 8u );
	unordered_set_t exp = unordered_set_create_from_array( ( int[ ] ) { 2, 4, 6, 8 }, 4u );

	assert( unordered_set_isEqual( unordered_set_complement( uset_a, uni ), exp ) );
}

ordered_set_t set_a, set_b;
void test_init_sets( ) {
	set_a = ordered_set_create_from_array( ( int[ ] ) { 1, 3, 5, 7 }, 4u );
	set_b = ordered_set_create_from_array( ( int[ ] ) { 3, 5, 6 }, 3u );
}

void test_ordered_set( ) {
	test_ordered_set_create_from_array( );

	test_ordered_set_in( );

	test_ordered_set_isSubset( );

	test_ordered_set_isEqual( );

	test_ordered_set_insert( );

	test_ordered_set_delete( );

	test_ordered_set_union( );

	test_ordered_set_intersection( );

	test_ordered_set_diff( );

	test_ordered_set_symdiff( );

	test_ordered_set_complement( );
}

void test_ordered_set_create_from_array( ) {
	test_init_sets( );

	ordered_set_t res1 = ordered_set_create( 4u );
	ordered_set_t res2 = ordered_set_create( 4u );

	ordered_set_insert( &res1, 1 );
	ordered_set_insert( &res1, 3 );
	ordered_set_insert( &res1, 5 );
	ordered_set_insert( &res1, 7 );

	ordered_set_insert( &res2, 3 );
	ordered_set_insert( &res2, 5 );
	ordered_set_insert( &res2, 6 );

	assert( ordered_set_isEqual( set_a, res1 ) );
	assert( ordered_set_isEqual( set_b, res2 ) );
}

void test_ordered_set_in( ) {
	assert( ordered_set_in( set_a, 1 ) == 0u );
	assert( ordered_set_in( set_a, 8 ) == set_a.m_size );
}

void test_ordered_set_isSubset( ) {
	ordered_set_t sub = ordered_set_create_from_array( ( int[ ] ) { 5, 7 }, 2u );

	assert( ordered_set_isSubset( sub, set_a ) != set_a.m_size );
	assert( ordered_set_isSubset( sub, set_b ) == set_b.m_size );
}

void test_ordered_set_isEqual( ) {
	ordered_set_t res1 = ordered_set_create( 4u );

	ordered_set_insert( &res1, 1 );
	ordered_set_insert( &res1, 3 );
	ordered_set_insert( &res1, 5 );
	ordered_set_insert( &res1, 7 );

	assert( ordered_set_isEqual( res1, set_a ) );
	assert( !ordered_set_isEqual( set_b, set_a ) );
}

void test_ordered_set_insert( ) {
	ordered_set_t ab = ordered_set_create( 2 );
	ordered_set_insert( &ab, 1337 );

	assert( ordered_set_in( ab, 1337 ) == 0u );
}

void test_ordered_set_delete( ) {
	ordered_set_t ab = ordered_set_create( 2 );
	ordered_set_insert( &ab, 228 );
	ordered_set_insert( &ab, 1337 );

	ordered_set_delete( &ab, 1337 );

	assert( ordered_set_in( ab, 228 ) == 0u );
	assert( ordered_set_in( ab, 1337 ) == ab.m_size );
}
void test_ordered_set_union( ) {
	ordered_set_t res = ordered_set_union( set_a, set_b );
	ordered_set_t exp = ordered_set_create_from_array( ( int[ ] ) { 1, 3, 5, 6, 7 }, 5u );

	assert( ordered_set_isEqual( res, exp ) );
}
void test_ordered_set_intersection( ) {
	ordered_set_t res = ordered_set_intersection( set_a, set_b );
	ordered_set_t exp = ordered_set_create_from_array( ( int[ ] ) { 3, 5 }, 2u );

	assert( ordered_set_isEqual( res, exp ) );
}

void test_ordered_set_diff( ) {
	ordered_set_t res = ordered_set_diff( set_a, set_b );
	ordered_set_t exp = ordered_set_create_from_array( ( int[ ] ) { 1, 7 }, 2u );

	assert( ordered_set_isEqual( res, exp ) );
}

void test_ordered_set_symdiff( ) {
	ordered_set_t res = ordered_set_symdiff( set_a, set_b );
	ordered_set_t exp = ordered_set_create_from_array( ( int[ ] ) { 1, 6, 7 }, 3u );

	assert( ordered_set_isEqual( res, exp ) );
}

void test_ordered_set_complement( ) {
	ordered_set_t uni = ordered_set_create_from_array( ( int[ ] ) { 1, 2, 3, 4, 5, 6, 7, 8 }, 8u );
	ordered_set_t exp = ordered_set_create_from_array( ( int[ ] ) { 2, 4, 6, 8 }, 4u );

	assert( ordered_set_isEqual( ordered_set_complement( set_a, uni ), exp ) );
}