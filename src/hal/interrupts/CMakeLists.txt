#############################################################################################################################
# file:  hal/interrupts/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/stm32h5xx_it.c
	src/hal_it.c
	src/error_handler.c
)

# Creating the library
add_library(INTERRUPTS STATIC ${SOURCES})

# Link against the HAL
target_link_libraries(INTERRUPTS ST_HAL)

# Adding the include folder
target_include_directories(INTERRUPTS PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)
