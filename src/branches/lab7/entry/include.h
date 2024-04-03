#include <stdio.h>

typedef struct vdvector vdvector_t;

typedef struct polynomial {
	int m_power;
	int m_coeff;
} polynomial_t;

void task01( vdvector_t *ms );

void task02( vdvector_t *v );

void task03( int *v );

void task06( float x, vdvector_t *v );

void run_branch( );