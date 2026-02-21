#############################################################################################################################
# file:  tasks/muxer/CMakeLists.txt
# brief: Main data router inside the project
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/launcher.c
)

# Creating the library
add_library(LAUNCHER STATIC ${SOURCES})

# Ensure the library link against the right libs
target_link_libraries(LAUNCHER 
	HAL 
	THREADX_OS
	HARDWARE
	IDLE
	INET
	IFACE
	MUXER
	VCOM
)


# Adding the include folder
target_include_directories(LAUNCHER PUBLIC include/)
