#include "../include.h"

#include <matrix/include.h>

#include <vdvector/include.h>

#include <exceptions/include.h>

void gWriteMatrix( const char *file_name, vdvector_t ms ) {
	FILE *write = fopen( file_name, "w" );
	if ( write == NULL )
		STD_ERROR_N_EXIT( gWriteMatrix, "cannot open file" );

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

void gWriteFloat( const char *file_name, vdvector_t v, const char *format ) {
	FILE *write = fopen( file_name, "w" );
	if ( write == NULL )
		STD_ERROR_N_EXIT( gWriteFloat, "cannot open file" );

	for ( size_t i = 0u; i < v.m_size; ++i ) {
		float f;
		vdvector_get( &v, i, &f );

		fprintf( write, format, f );
	}

	fclose( write );
}

void gWriteLine( const char *file_name, const char *line ) {
	FILE *write = fopen( file_name, "w" );
	if ( write == NULL )
		STD_ERROR_N_EXIT( gWriteLine, "cannot open file" );

	fprintf( write, line );

	fclose( write );
}