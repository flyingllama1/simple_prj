include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab8_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab8_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_7
	${src_lab8_tests}
	${src_lab8_entry}
)