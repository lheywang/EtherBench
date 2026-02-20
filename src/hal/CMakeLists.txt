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
add_subdirectory(startup)
add_subdirectory(system)

# Creating an higher level library (to prevent from the user to lin against too much libs)
add_library(HAL INTERFACE)

target_link_libraries(HAL INTERFACE
    SYSTEM
    STARTUP
)

# ADD INIT & ST_HAL when sources will be present
