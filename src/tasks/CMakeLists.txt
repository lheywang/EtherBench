#############################################################################################################################
# file:  tasks/CMakeLists.txt
# brief: RTOS Tasks build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(configuration)
add_subdirectory(files)
add_subdirectory(hardware)
add_subdirectory(inet)
add_subdirectory(leds)
add_subdirectory(logger)
add_subdirectory(muxer)
add_subdirectory(parser)
add_subdirectory(programmer)
add_subdirectory(sequences)
add_subdirectory(usb)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(TASKS INTERFACE)

target_link_libraries(TASKS INTERFACE
    CONFIG
	FILE_IO
	HARDWARE
	INET
	LEDS
	LOGGER
	MUXER
    PARSER
	PROGRAMMER
    SEQUENCES
	USB
)
