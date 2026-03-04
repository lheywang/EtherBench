#############################################################################################################################
# file:  tasks/parser/CMakeLists.txt
# brief: Main command parser build logic
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_parser.cpp
)

# Creating the library
add_library(PARSER STATIC ${SOURCES})

# Adding the include folder
target_include_directories(PARSER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)