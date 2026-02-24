#############################################################################################################################
# file:  tasks/muxer/CMakeLists.txt
# brief: Main data router inside the project
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/launcher.c
)

# Creating the library
add_library(LAUNCHER OBJECT ${SOURCES})

# Ensure the library link against the right libs
target_link_libraries(LAUNCHER 
	HAL 
	THREADX
	TASKS
)

# Adding the include folder
target_include_directories(LAUNCHER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)

