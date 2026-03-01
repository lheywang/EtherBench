#############################################################################################################################
# file:  tasks/idle/CMakeLists.txt
# brief: Task executed when nothing need to be done...
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_leds.cpp
)

# Creating the library
add_library(LEDS OBJECT ${SOURCES})

# Link against the right libraries
target_link_libraries(LEDS THREADX)

# Adding the include folder
target_include_directories(LEDS PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)
