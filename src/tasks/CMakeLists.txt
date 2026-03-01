#############################################################################################################################
# file:  tasks/CMakeLists.txt
# brief: RTOS Tasks build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(controller)
add_subdirectory(files)
add_subdirectory(hardware)
add_subdirectory(inet)
add_subdirectory(leds)
add_subdirectory(muxer)
add_subdirectory(programmer)
add_subdirectory(usb)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(TASKS INTERFACE)

# Ensure CMake will propagate objects upward
target_sources(TASKS INTERFACE
	$<TARGET_OBJECTS:CONTROLLER>
	$<TARGET_OBJECTS:FILES>
    $<TARGET_OBJECTS:HARDWARE>
    $<TARGET_OBJECTS:INET>
    $<TARGET_OBJECTS:LEDS>
    $<TARGET_OBJECTS:MUXER>
    $<TARGET_OBJECTS:PROGRAMMER>
    $<TARGET_OBJECTS:USB>
)

target_link_libraries(TASKS INTERFACE
	CONTROLLER
	FILES
	HARDWARE
	INET
	LEDS
	MUXER
	PROGRAMMER
	USB
)
