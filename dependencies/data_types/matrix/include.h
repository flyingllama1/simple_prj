#include <malloc.h>

typedef struct matrix {
	int **m_values;
	int m_rows;
	int m_cols;
} matrix_t;

typedef struct position {
	int m_row;
	int m_col;
} matpos_t;

matrix_t	getMemMatrix( int rows, int cols );

matrix_t	*getMemArrayOfMatrices( int matrices, int rows, int cols );

void		freeMemMatrix( matrix_t *mat );

void		freeMemMatrices( matrix_t *mat, int matrices );

void inputMatrix( matrix_t *mat );

void outputMatrix( const matrix_t mat );

void inputMatrices( matrix_t *mat, int matrices );

void outputMatrices( const matrix_t *mat, int matrices );

void swapRows( matrix_t mat, int i, int j );

void swapColumns( matrix_t mat, int i, int j );

void insertionSortRowsMatrixByRowCriteria( matrix_t mat, int( *criteria )( int *, int ) );

void selectionSortColsMatrixByColCriteria( matrix_t mat, int( *criteria )( int *, int ) );

int isSquareMatrix( matrix_t *mat );

int areTwoMatricesEqual( matrix_t *m1, matrix_t *m2 );

int isEMatrix( matrix_t *mat );

int isSymmetricMatrix( matrix_t *mat );

void transposeSquareMatrix( matrix_t *mat );

void transposeMatrix( matrix_t *mat );

matpos_t getMinValuePos( matrix_t mat );

matpos_t getMaxValuePos( matrix_t mat );

matrix_t createMatrixFromArray( const int *array, int rows, int cols );

matrix_t *createMatrixOfFromArray( const int *values, int matrices, int rows, int cols );

void sortRowsByMinElement( matrix_t mat );

void sortColsByMinElement( matrix_t mat );

matrix_t mulMatrices( matrix_t *m1, matrix_t *m2 );

void transposeIfMatrixHasNotEqualSumOfRows( matrix_t *mat );

int isMutuallyInverseMatrices( matrix_t m1, matrix_t m2 );

long long findSumOfMaxesOfPseudoDiagonal( matrix_t mat );

int getMinInArea( matrix_t mat );

float getDistance( int *a, int n );
void insertionSortRowsMatrixByRowCriteriaF( matrix_t m, float ( *criteria )( int *, int ) );
void sortByDistances( matrix_t m );