include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_files_vector ${CMAKE_CURRENT_LIST_DIR}/vector/*.[ch])

set (src_data_types
	${src_files_vector}
)