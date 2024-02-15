#include <stdio.h>
#include <assert.h>

int max2( const int a, const int b );

size_t binsrch( const int *array, const size_t size, const int x );

size_t binsrch_me( const int *array, const size_t size, const int x );

void swap( void *a, void *b, const size_t type_size );

void iswap( int *a, int *b );

int getMaxElementIndexInArray( int *const n, const size_t size );

int getMinElementIndexInArray( int *const n, const size_t size );

void ascan( int *array, const size_t size );

void aprint( const int *array, const size_t size );