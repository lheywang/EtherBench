#############################################################################################################################
# file:  tasks/inet/CMakeLists.txt
# brief: User network task build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/inet.cpp
)

# Creating the library
add_library(INET STATIC ${SOURCES})

# Adding the include folder
target_include_directories(INET PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)