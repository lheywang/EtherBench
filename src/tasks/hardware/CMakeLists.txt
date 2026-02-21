#############################################################################################################################
# file:  tasks/hardware/CMakeLists.txt
# brief: Hardware task build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/hardware.cpp
)

# Creating the library
add_library(HARDWARE STATIC ${SOURCES})

# Adding the include folder
target_include_directories(HARDWARE PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)