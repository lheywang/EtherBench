#############################################################################################################################
# file:  threadx/CMakeLists.txt
# brief: RTOS build file
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(threadx)
add_subdirectory(filex)
add_subdirectory(levelx)
add_subdirectory(netxduo)
add_subdirectory(usbx)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(THREADX INTERFACE)

# Ensure CMake will propagate objects upward (required otherwise USB won't enumerate at all !) 
# --> But that slow down the compilation !
target_sources(THREADX INTERFACE
    $<TARGET_OBJECTS:USBX>
)

# Some arguments are needed to ensure we link against the whole lib
target_link_libraries(THREADX INTERFACE 
	THREADX_OS
	USBX
	NETXDUO
	FILEX
	LEVELX
)
