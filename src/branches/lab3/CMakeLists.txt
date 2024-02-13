include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab3_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab3_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_2
	${src_lab3_tests}
	${src_lab3_entry}
)