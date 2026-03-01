#############################################################################################################################
# file:  tasks/usb/CMakeLists.txt
# brief: USB IO handling task.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_usb.cpp
)

# Creating the library
add_library(USB OBJECT ${SOURCES})

# Adding the include folder
target_include_directories(USB PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)