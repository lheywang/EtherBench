#############################################################################################################################
# file:  tasks/leds/CMakeLists.txt
# brief: Task executed to control leds IO.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_leds.cpp
)

# Creating the library
add_library(LEDS STATIC ${SOURCES})

# Link against the right libraries
target_link_libraries(LEDS THREADX HAL)

# Adding the include folder
target_include_directories(LEDS PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)
