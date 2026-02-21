#############################################################################################################################
# file:  hal/CMakeLists.txt
# brief: ST provided files build setup
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(hal)
add_subdirectory(init)
add_subdirectory(interrupts)
add_subdirectory(startup)
add_subdirectory(system)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(HAL INTERFACE)

# Some specific flags are required to ensure the linker won't throw away some precious interrupt handlers
# and other things like that.
target_link_libraries(HAL INTERFACE
    SYSTEM
    INIT
    "-Wl,--whole-archive"
    STARTUP
    INTERRUPTS
    ST_HAL
    "-Wl,--no-whole-archive"
)

