include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab2_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab2_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_1
	${src_lab2_tests}
	${src_lab2_entry}
)