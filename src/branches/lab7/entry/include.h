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

typedef struct product {
	char *m_name;
	int   m_price;
	int   m_full_price;
	int   m_count;
} product_t;

typedef struct procurement {
	char *m_name;
	int   m_count;
} procurement_t;

void task01( vdvector_t *ms );

void task02( vdvector_t *v );

void task03( int *v );

void task04( char *alphabet );

void task05( vdvector_t *s );

void task06( float x, vdvector_t *v );

void task07( vdvector_t *nums );

void task08( vdvector_t *ms );

void task09( int n, vdvector_t *v );

void task10( vdvector_t *v );

void run_branch( char **argv, int argc );