#############################################################################################################################
# file:  tasks/interface/CMakeLists.txt
# brief: User interface task build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/interface.cpp
)

# Creating the library
add_library(IFACE STATIC ${SOURCES})

# Adding the include folder
target_include_directories(IFACE PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)