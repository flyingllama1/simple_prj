include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab4_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab4_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_3
	${src_lab4_tests}
	${src_lab4_entry}
)