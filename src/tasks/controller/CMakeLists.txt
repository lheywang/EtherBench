#############################################################################################################################
# file:  tasks/inet/CMakeLists.txt
# brief: User network task build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_controller.cpp
)

# Creating the library
add_library(CONTROLLER OBJECT ${SOURCES})

# Adding the include folder
target_include_directories(CONTROLLER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)