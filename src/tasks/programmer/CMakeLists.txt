#############################################################################################################################
# file:  tasks/programmer/CMakeLists.txt
# brief: CMSIS programmer, in between others programming function.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_programmer.cpp
)

# Creating the library
add_library(PROGRAMMER OBJECT ${SOURCES})

# Adding the include folder
target_include_directories(PROGRAMMER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)