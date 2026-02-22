#############################################################################################################################
# file:  hal/init/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES
	 src/init.c
)

list(APPEND SOURCES
	src/peripherals/cordic.c
	src/peripherals/dcache.c
	src/peripherals/eth.c
	src/peripherals/fmac.c
	src/peripherals/gpio.c
	src/peripherals/icache.c
	src/peripherals/octospi.c
	src/peripherals/rcc.c
	src/peripherals/sdmmc.c
	src/peripherals/stm32h5xx_hal_msp.c
	src/peripherals/usart.c
	src/peripherals/usb.c
)


# Creating the library
add_library(INIT STATIC ${SOURCES})

# Link against the HAL
target_link_libraries(INIT ST_HAL INTERRUPTS)

# Adding the include folder
target_include_directories(INIT PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/include/peripherals/
)
target_include_directories(INIT PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
