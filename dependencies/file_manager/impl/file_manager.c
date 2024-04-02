#include "../include.h"

#include <matrix/include.h>
#include <vdvector/include.h>

void gWriteMatrix( const char *file_name, vdvector_t ms ) {
	FILE *write = fopen( file_name, "w" );

	for ( size_t i = 0u; i < ms.m_size; ++i ) {
		matrix_t mx;
		vdvector_get( &ms, i, &mx );

		fprintf( write, "%d\n", mx.m_cols );
		for ( size_t r = 0u; r < mx.m_rows; ++r ) {
			for ( size_t c = 0u; c < mx.m_cols; ++c ) {
				fprintf( write, "%d ", mx.m_values[ r ][ c ] );
			}

			fprintf( write, "\n" );
		}
	}

	fclose( write );
}