include_directories (${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_lab1_tests ${CMAKE_CURRENT_LIST_DIR}/tests/*.[ch])
file (GLOB_RECURSE src_lab1_entry ${CMAKE_CURRENT_LIST_DIR}/entry/*.[ch])

set (src_branch_0 
	${src_lab1_tests}
	${src_lab1_entry}
)