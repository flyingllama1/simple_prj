#include "../include.h"

#include <memory.h>
#include <malloc.h>
#include <math.h>

int min2( const int a, const int b ) {
    return a > b ? b : a;
}

int max2( const int a, const int b ) {
    return a > b ? a : b;
}

size_t binsrch( const int *array, const size_t size, const int x ) {
    if ( !size )
        return 0u;

    size_t low  = 0u;
    size_t high = size - 1u;
    while ( low <= high && low <= size && high <= size ) {
        size_t middle = low + ( high - low ) / 2;
        if ( array[ middle ] < x ) {
            low = middle + 1u;
        } else if ( array[ middle ] > x ) {
            high = middle - 1u;
        } else {
            return middle;
        }
    }

    return size;
}

size_t binsrch_me( const int *array, const size_t size, const int x ) {
    if ( array[ 0 ] >= x )
        return 0u;

    size_t low  = 0u;
    size_t high = size;
    while ( low + 1 < high ) {
        size_t middle = low + ( high - low ) / 2u;
        if ( array[ middle ] < x ) {
            low = middle;
        }
        else {
            high = middle;
        }
    }
    return high;
}

void swap( void *a, void *b, const size_t type_size ) {
    char *src = malloc( type_size );

    memcpy( src, a, type_size );
    memcpy( a, b, type_size );
    memcpy( b, src, type_size );

    free( src );
}

void swapInt( int *a, int *b ) {
    swap( a, b, sizeof( int ) );
}

int getElementIndexInArrayIf_( int *const array, const size_t size, int( *comp )( int, int ) ) {
    int req = array[ 0 ];

    size_t index = 0u;
    for ( size_t i = 1u; i < size; ++i ) {
        if ( comp( array[ i ], req ) ) {
            req = array[ i ];
            index = i;
        }
    }

    return index;
}

int _compMax( int a, int req ) { return a > req; }

int getMaxElementIndexInArray( int *const array, const size_t size ) {
    return getElementIndexInArrayIf_( array, size, _compMax );
}

int _compMin( int a, int req ) { return a < req; }

int getMinElementIndexInArray( int *const array, const size_t size ) {
    return getElementIndexInArrayIf_( array, size, _compMin );
}

void ascan( int *array, const size_t size ) {
    for ( size_t i = 0u; i < size; ++i )
        scanf( "%d", &array[ i ] );
}

void aprint( const int *array, const size_t size ) {
    for ( size_t i = 0u; i < size; ++i )
        printf( "%d ", array[ i ] );

    printf( "%d\n" );
}

float getDistance( const int *array, const size_t size ) {
    float ret = 0.f;
    for ( size_t i = 0u; i < size; ++i )
        ret += ( array[ i ] * array[ i ] );

    return sqrtf( ret );
}

int isNonDescendingSorted( const int *array, const size_t size ) {
    for ( size_t i = 1u; i < size; ++i ) {
        if ( array[ i ] < array[ i - 1 ] )
            return 0;
    }

    return 1;
}