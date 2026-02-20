#############################################################################################################################
# file:  bsp/ethernet/CMakeLists.txt
# brief: ST provided files build setup
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(lan8742)

# Creating an higher level library (to prevent from the user to lin against too much libs)
# There's only one lib, okay, but we stay consistent
add_library(ETHERNET INTERFACE)

target_link_libraries(HAL INTERFACE
	LAN8742
)
