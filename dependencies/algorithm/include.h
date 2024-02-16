#include <stdio.h>
#include <assert.h>

int min2( const int a, const int b );

int max2( const int a, const int b );

size_t binsrch( const int *array, const size_t size, const int x );

size_t binsrch_me( const int *array, const size_t size, const int x );

void swap( void *a, void *b, const size_t type_size );

void swapInt( int *a, int *b );

int getElementIndexInArrayIf_( int *const array, const size_t size, int( *comp )( int, int ) );

int getMaxElementIndexInArray( int *const array, const size_t size );

int getMinElementIndexInArray( int *const array, const size_t size );

void ascan( int *array, const size_t size );

void aprint( const int *array, const size_t size );

float getDistance( const int *array, const size_t size );

int isNonDescendingSorted( const int *array, const size_t size );

int countValues( const int *array, const size_t size, const int value );