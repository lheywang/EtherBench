#############################################################################################################################
# file:  tasks/configuration/CMakeLists.txt
# brief: Main configuration, board level task.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_configuration.cpp
)

# Creating the library
add_library(CONFIG STATIC ${SOURCES})

# Adding the include folder
target_include_directories(CONFIG PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)