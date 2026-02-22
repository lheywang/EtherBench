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

# Some arguments are needed to ensure we link against the whole lib
target_link_libraries(THREADX INTERFACE 
	"-Wl,--whole-archive"
	THREADX_OS
	"-Wl,--no-whole-archive"
	USBX
)

# ADD FILEX LEVELX NETXDUO  USBX libs, when sources will be available