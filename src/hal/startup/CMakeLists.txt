#############################################################################################################################
# file:  hal/startup/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/startup_stm32h563zitx.s
)

# Creating the library
add_library(STARTUP STATIC ${SOURCES})

# Adding the include folder (empty here)
# target_include_directories(SYSTEM PUBLIC include/)