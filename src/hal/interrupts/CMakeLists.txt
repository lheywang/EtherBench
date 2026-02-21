#############################################################################################################################
# file:  hal/startup/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/stm32h5xx_it.c
)

# Creating the library
add_library(INTERRUPTS STATIC ${SOURCES})

# Adding the include folder (empty here)
target_include_directories(INTERRUPTS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)