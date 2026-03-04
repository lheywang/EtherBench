#############################################################################################################################
# file:  tasks/files/CMakeLists.txt
# brief: File manager for both QSPI and SD files systems.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_files.cpp
)

# Creating the library
add_library(FILE_IO STATIC ${SOURCES})

# Adding the include folder
target_include_directories(FILE_IO PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)