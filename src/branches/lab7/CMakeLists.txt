include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab7_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab7_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_6
	${src_lab7_tests}
	${src_lab7_entry}
)