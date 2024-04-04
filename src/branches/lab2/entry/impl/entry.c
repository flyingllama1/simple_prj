#include "../include.h"

#include "../../tests/include.h"

#include <vector/include.h>

#include <vdvector/include.h>

void run_branch( char **argv, int argc ) {
	test_vector_content0( );

	test_vector_content1( );

	test_vdvector_content0( );

	return 0;
}
