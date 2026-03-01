#############################################################################################################################
# file:  tasks/logger/CMakeLists.txt
# brief: Deferred logging process.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_logger.cpp
)

# Creating the library
add_library(LOGGER OBJECT ${SOURCES})

target_link_libraries(LOGGER THREADX_OS)

# Adding the include folder
target_include_directories(LOGGER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)