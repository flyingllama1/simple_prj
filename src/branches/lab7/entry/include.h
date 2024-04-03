#include <stdio.h>

typedef struct vdvector vdvector_t;

typedef struct polynomial {
	int m_power;
	int m_coeff;
} polynomial_t;

typedef struct sportsman {
	char *m_name;
	int   m_result;
} sportsman_t;

void task01( vdvector_t *ms );

void task02( vdvector_t *v );

void task03( int *v );

void task04( char *alphabet );

void task05( vdvector_t *s );

void task06( float x, vdvector_t *v );

void task07( vdvector_t *nums );

void task08( vdvector_t *ms );

void task09( int n, vdvector_t *v );

void run_branch( );