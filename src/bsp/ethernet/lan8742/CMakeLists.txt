#############################################################################################################################
# file:  bsp/ethernet/lan8742/CMakeLists.txt
# brief: Ethernet chip drivers
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/lan8742.c
)

# Creating the library
add_library(LAN8742 STATIC ${SOURCES})

# Adding the include folder (empty here)
target_include_directories(LAN8742 PUBLIC include/)