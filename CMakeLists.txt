cmake_minimum_required (VERSION 3.8)

project ("cproject")

include ("dependencies/CMakeLists.txt")
include ("src/branches/CMakeLists.txt")

set (src_files
	"src/main.c" "src/main.h"
	${src_dependencies}
	${src_branch}
)

add_executable (cproject ${src_files})

target_sources (cproject PRIVATE ${src_files})
source_group (TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${src_files})
	
set_property(TARGET cproject PROPERTY CXX_STANDARD 20)