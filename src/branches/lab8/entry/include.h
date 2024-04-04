#include <stdio.h>

typedef struct vdvector vdvector_t;
typedef struct matrix matrix_t;

typedef struct domain_info {
	char  m_name[ 1024u ];
	int   m_visits;
} domain_info_t;

void task01( matrix_t *mm, int queries[ ][ 4 ], const size_t queries_amt );

void task02( matrix_t *m0, matrix_t *m1 );

void task03( matrix_t *m0, matrix_t *m1 );

void task04( char *domains[ ], const size_t domains_amt, vdvector_t *subdomains );

void task05( matrix_t *mm, int *submatrices );

void task06( char *sig, int *res );

void task07( );

void task08( );

void task09( );

void task10( );

void run_branch( );