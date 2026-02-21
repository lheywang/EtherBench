#############################################################################################################################
# file:  hal/CMakeLists.txt
# brief: ST provided files build setup
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(ethernet)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(BSP INTERFACE)

target_link_libraries(BSP INTERFACE
    ETHERNET
)
