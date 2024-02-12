include_directories (${CMAKE_CURRENT_LIST_DIR})

include ("dependencies/data_types/CMakeLists.txt")

file (GLOB_RECURSE src_files_algorithm ${CMAKE_CURRENT_LIST_DIR}/algorithm/*.[ch])

file (GLOB_RECURSE src_files_bit_set ${CMAKE_CURRENT_LIST_DIR}/bit_set/*.[ch])

file (GLOB_RECURSE src_files_unordered_set ${CMAKE_CURRENT_LIST_DIR}/unordered_set/*.[ch])

file (GLOB_RECURSE src_files_ordered_set ${CMAKE_CURRENT_LIST_DIR}/ordered_set/*.[ch])

set (src_dependencies
	${src_files_algorithm}
	${src_files_bit_set}
	${src_files_unordered_set}
	${src_files_ordered_set}
	${src_data_types}
)