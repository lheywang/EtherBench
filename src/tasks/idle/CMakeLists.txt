#############################################################################################################################
# file:  tasks/idle/CMakeLists.txt
# brief: Task executed when nothing need to be done...
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/idle.cpp
)

# Creating the library
add_library(IDLE STATIC ${SOURCES})

# Link against the right libraries
target_link_libraries(IDLE THREADX_OS)

# Adding the include folder
target_include_directories(IDLE PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)
