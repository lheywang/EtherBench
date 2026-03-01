#############################################################################################################################
# file:  tasks/interface/CMakeLists.txt
# brief: User interface task build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_files.cpp
)

# Creating the library
add_library(FILES OBJECT ${SOURCES})

# Adding the include folder
target_include_directories(FILES PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)