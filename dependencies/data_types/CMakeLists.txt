include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_files_vector ${CMAKE_CURRENT_LIST_DIR}/vector/*.[ch])

file (GLOB_RECURSE src_files_vdvector ${CMAKE_CURRENT_LIST_DIR}/vdvector/*.[ch])

file (GLOB_RECURSE src_files_matrix ${CMAKE_CURRENT_LIST_DIR}/matrix/*.[ch])

file (GLOB_RECURSE src_files_string ${CMAKE_CURRENT_LIST_DIR}/string/*.[ch])

set (src_data_types
	${src_files_vector}
	${src_files_vdvector}
	${src_files_matrix}
	${src_files_string}
)