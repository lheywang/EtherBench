#############################################################################################################################
# file:  CMakeLists.txt
# brief: Main build file, for the project.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)
project("EtherBench")
enable_language(ASM C CXX)

# We just need to configure variables
add_compile_definitions(
	-DUSE_HAL_DRIVER 
	-DSTM32H563xx
	-DTX_SINGLE_MODE_NON_SECURE
)

# Add the config directory, which is global
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/config)

# We only add the main.c file, all the remaining is built arround libraries.
add_executable(${CMAKE_PROJECT_NAME} main.c)

# Add the different folders
add_subdirectory(threadx)
add_subdirectory(tasks)
add_subdirectory(hal)
add_subdirectory(bsp)
add_subdirectory(launcher)

# Add libraries
# Will need to add TASKS when they're complete !
target_link_libraries(${PROJECT_NAME} 
	HAL 
	BSP
	TASKS
	LAUNCHER
	THREADX
)

