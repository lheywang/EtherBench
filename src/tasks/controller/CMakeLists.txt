#############################################################################################################################
# file:  tasks/controller/CMakeLists.txt
# brief: Main command parser and controller build logic
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_controller.cpp
)

# Creating the library
add_library(CONTROLLER STATIC ${SOURCES})

# Adding the include folder
target_include_directories(CONTROLLER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)