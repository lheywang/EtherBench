#############################################################################################################################
# file:  hal/startup/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/stm32h5xx_hal_cordic.c
	src/stm32h5xx_hal_cortex.c
	src/stm32h5xx_hal_dcache.c
	src/stm32h5xx_hal_dma_ex.c
	src/stm32h5xx_hal_dma.c
	src/stm32h5xx_hal_eth_ex.c
	src/stm32h5xx_hal_eth.c
	src/stm32h5xx_hal_exti.c
	src/stm32h5xx_hal_flash_ex.c
	src/stm32h5xx_hal_flash.c
	src/stm32h5xx_hal_fmac.c
	src/stm32h5xx_hal_gpio.c
	src/stm32h5xx_hal_icache.c
	src/stm32h5xx_hal_mmc_ex.c
	src/stm32h5xx_hal_mmc.c
	src/stm32h5xx_hal_pcd_ex.c
	src/stm32h5xx_hal_pcd.c
	src/stm32h5xx_hal_pwr_ex.c
	src/stm32h5xx_hal_pwr.c
	src/stm32h5xx_hal_rcc_ex.c
	src/stm32h5xx_hal_rcc.c
	src/stm32h5xx_hal_sd_ex.c
	src/stm32h5xx_hal_sd.c
	src/stm32h5xx_hal_sdio.c
	src/stm32h5xx_hal_tim_ex.c
	src/stm32h5xx_hal_tim.c
	src/stm32h5xx_hal_timebase_tim.c
	src/stm32h5xx_hal_uart_ex.c
	src/stm32h5xx_hal_uart.c
	src/stm32h5xx_hal_xspi.c
	src/stm32h5xx_hal.c
	src/stm32h5xx_ll_dlyb.c
	src/stm32h5xx_ll_sdmmc.c
	src/stm32h5xx_ll_usb.c
)

# Creating the library
add_library(ST_HAL STATIC ${SOURCES})

# Adding the include folder
target_include_directories(ST_HAL PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	${CMAKE_CURRENT_SOURCE_DIR}/include/cmsis/
)
