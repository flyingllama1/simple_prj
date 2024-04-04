#include "../include.h"

#include "../../tests/include.h"

#include <exceptions/include.h>

#include <vdvector/include.h>

#include <matrix/include.h>

#include <file_manager/include.h>

#include <string/include.h>

#include <string.h>

void task01( matrix_t *mm, int queries[ ][ 4 ], const size_t queries_amt ) {
	for ( size_t i = 0u; i < queries_amt; ++i ) {
		int *query = queries[ i ];
		for ( size_t row = query[ 0 ]; row <= query[ 2 ]; ++row ) {
			for ( size_t col = query[ 1 ]; col <= query[ 3 ]; ++col ) {
				mm->m_values[ row ][ col ] += 1;
			}
		}
	}
}

int countNeighbourPoints( matrix_t *mm, int row, int col ) {
	int left = max( 0, col - 1 );
	int head = max( 0, row - 1 );
	int right = min( mm->m_cols - 1u, col + 1 );
	int bot = min( mm->m_rows - 1u, row + 1 );

	int neighbours = 0;
	for ( size_t i = head; i <= bot; ++i )
		for ( size_t j = left; j <= right; ++j )
			if ( mm->m_values[ i ][ j ] == 1 && ( col != j || row != i ) )
				++neighbours;

	return neighbours;
}

void task02( matrix_t *m0, matrix_t *m1 ) {
	for ( size_t i = 0u; i < m0->m_rows; ++i ) {
		for ( size_t j = 0u; j < m0->m_cols; ++j ) {
			int neighbours = countNeighbourPoints( m0, i, j );

			m1->m_values[ i ][ j ] = 1;
			if ( m0->m_values[ i ][ j ] == 1 ) {
				if ( neighbours < 2 || neighbours > 3 )
					m1->m_values[ i ][ j ] = 0;
			}
			else {
				if ( neighbours != 3 )
					m1->m_values[ i ][ j ] = 0;
			}
		}
	}
}

void getNeighbourPoints( vdvector_t *points, matrix_t *mm, int row, int col ) {
	int left = max( 0, col - 1 );
	int head = max( 0, row - 1 );
	int right = min( mm->m_cols - 1u, col + 1 );
	int bot = min( mm->m_rows - 1u, row + 1 );

	for ( size_t i = head; i <= bot; ++i )
		for ( size_t j = left; j <= right; ++j )
			if ( col != j || row != i )
				vdvector_pushBack( points, &mm->m_values[ i ][ j ] );
}

int compareNeighbourPoints( const void *pa, const void *pb ) {
	int a = *( const int * )pa;
	int b = *( const int * )pb;

	return a - b;
}

void task03( matrix_t *m0, matrix_t *m1 ) {
	for ( size_t i = 0u; i < m0->m_rows; ++i ) {
		for ( size_t j = 0u; j < m0->m_cols; ++j ) {
			if ( i == 0u || j == 0u || i == m0->m_rows - 1u || j == m0->m_cols - 1u )
				m1->m_values[ i ][ j ] = m0->m_values[ i ][ j ];
			else {
				vdvector_t neighbours = vdvector_create( 0u, sizeof( int ) );
				getNeighbourPoints( &neighbours, m0, i, j );
				qsort( neighbours.m_data, neighbours.m_size, neighbours.m_base_type_size, compareNeighbourPoints );

				int md;
				vdvector_get( &neighbours, neighbours.m_size / 2, &md );
				m1->m_values[ i ][ j ] = md;
			}
		}
	}
}

void task04( char *domains[ ], const size_t domains_amt, vdvector_t *subdomains ) {
	for ( size_t i = 0u; i < domains_amt; ++i ) {
		char  domain[ 1024u ];
		int	  visits;
		memset( domain, 0, sizeof( char ) * 1024u );
		sscanf( domains[ i ], "%d %s", &visits, &domain );

		vdvector_t sb_names = vdvector_create( 0u, sizeof( char * ) );
		char *tok = strtok( domain, "." );

		while ( tok != NULL ) {
			vdvector_pushBack( &sb_names, &tok );

			tok = strtok( NULL, "." );
		}


		for ( size_t j = 0u; j < sb_names.m_size; ++j ) {
			char new_name[ 1024u ];
			memset( new_name, 0, sizeof( char ) * 1024u );

			for ( size_t k = j; k < sb_names.m_size; ++k ) {
				char *name;
				vdvector_get( &sb_names, k, &name );

				strcat( new_name, name );
				if ( k != sb_names.m_size - 1u )
					strcat( new_name, "." );
			}

			int is_in_domains = 0;
			for ( size_t i = 0u; i < subdomains->m_size; ++i ) {
				domain_info_t info;
				vdvector_get( subdomains, i, &info );

				if ( strcmp( info.m_name, new_name ) == 0 ) {
					is_in_domains = 1;
					info.m_visits += visits;
					vdvector_set( subdomains, i, &info );
					break;
				}
			}

			if ( !is_in_domains ) {
				domain_info_t new_domain;
				strcpy( new_domain.m_name, new_name );
				new_domain.m_visits = visits;

				vdvector_pushBack( subdomains, &new_domain );
			}
		}
	}
}

void task05( matrix_t *mm, int *submatrices ) {
	matrix_t sq = getMemMatrix( mm->m_rows, mm->m_cols );
	for ( size_t i = 0u; i < mm->m_rows; ++i ) {
		for ( size_t j = 0u; j < mm->m_cols; ++j ) {
			if ( i == 0u && mm->m_values[ i ][ j ] == 1 )
				sq.m_values[ i ][ j ] = 1;
			else if ( mm->m_values[ i ][ j ] == 1 ) {
				sq.m_values[ i ][ j ] = sq.m_values[ i - 1 ][ j ] + 1;
			}
		}
	}

//	outputMatrix( dp );

	for ( size_t i = 0u; i < mm->m_rows; ++i ) {
		for ( size_t j = 0u; j < mm->m_cols; ++j ) {
			for ( size_t k = j + 1u; k < mm->m_cols + 1u; ++k ) {
				int m = sq.m_values[ i ][ j ];
				for ( size_t v = j; v < k; ++v )
					m = min( m, sq.m_values[ i ][ v ] );
				( *submatrices ) += m;
			}
		}
	}
}

void task06( char *sig, int *res ) {
	char buf[ 1024u ];
	int  stack[ 1024u ];

	int size = strlen_( sig );
	int stack_size = 0;
	int buffer_size = 0;
	int n = 1;

	for ( size_t i = 0u; i < size; ++i ) {
		stack[ stack_size++ ] = n++;
		if ( sig[ i ] == 'I' ) {
			while ( stack_size > 0 )
				buf[ buffer_size++ ] = stack[ --stack_size ] + '0';
		}
	}

	stack[ stack_size++ ] = n;
	while ( stack_size > 0 )
		buf[ buffer_size++ ] = stack[ --stack_size ] + '0';

	buf[ buffer_size ] = '\0';

	*res = atoi( buf );
}

node_t *constructNode( int *arr, const size_t size ) {
	if ( size == 0u )
		return NULL;

	int mx = 0u;
	for ( size_t i = 1u; i < size; ++i )
		if ( arr[ mx ] < arr[ i ] )
			mx = i;

	node_t *node = ( node_t * )malloc( sizeof( node_t ) );

	node->m_value = arr[ mx ];
	node->m_left = constructNode( arr, mx );
	node->m_right = constructNode( arr + mx + 1u, size - mx - 1u );

	return node;
}

node_t *task07( const int *arr, const size_t size, node_t *tree ) {
	return constructNode( arr, size );
}

void run_branch( ) {
	test_lab_content( );
}