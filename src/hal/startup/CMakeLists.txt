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
	src/system_stm32h5xx.c
)

# Creating the library
add_library(STARTUP STATIC ${SOURCES})

target_link_libraries(STARTUP ST_HAL)

# There's no include, source only. Nothing to be included.
