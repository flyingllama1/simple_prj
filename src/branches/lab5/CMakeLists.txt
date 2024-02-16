include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab5_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab5_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_4
	${src_lab5_tests}
	${src_lab5_entry}
)