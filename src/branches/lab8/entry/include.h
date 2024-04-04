#include <stdio.h>

typedef struct vdvector vdvector_t;
typedef struct matrix matrix_t;

typedef struct domain_info {
	char  m_name[ 1024u ];
	int   m_visits;
} domain_info_t;

typedef struct node {
	int     m_value;

	struct node *m_left;
	struct node *m_right;
} node_t;

void task01( matrix_t *mm, int queries[ ][ 4 ], const size_t queries_amt );

void task02( matrix_t *m0, matrix_t *m1 );

void task03( matrix_t *m0, matrix_t *m1 );

void task04( char *domains[ ], const size_t domains_amt, vdvector_t *subdomains );

void task05( matrix_t *mm, int *submatrices );

void task06( char *sig, int *res );

node_t *task07( const int *arr, const size_t size );

void task08( char *s, const int *indices );

void task09( );

void task10( );

void run_branch( );