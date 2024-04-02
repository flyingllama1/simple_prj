#include <stdio.h>

typedef struct vdvector vdvector_t;

void gWriteMatrix( const char *file_name, vdvector_t ms );

void gWriteFloat( const char *file_name, vdvector_t v, const char *format );