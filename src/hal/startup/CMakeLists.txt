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

# There's no include, source only. Nothing to be included.