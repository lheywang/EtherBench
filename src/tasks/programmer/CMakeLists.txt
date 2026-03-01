#############################################################################################################################
# file:  tasks/inet/CMakeLists.txt
# brief: User network task build
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