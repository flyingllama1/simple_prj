include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab6_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab6_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_5
	${src_lab6_tests}
	${src_lab6_entry}
)