#############################################################################################################################
# file:  tasks/CMakeLists.txt
# brief: RTOS Tasks build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(hardware)
add_subdirectory(idle)
add_subdirectory(inet)
add_subdirectory(interface)
add_subdirectory(muxer)
add_subdirectory(vcom)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(TASKS INTERFACE)

target_link_libraries(TASKS INTERFACE
	HARDWARE
	IDLE
	INET
	IFACE
	MUXER
	VCOM
)
