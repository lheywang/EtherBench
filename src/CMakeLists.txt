#############################################################################################################################
# file:  CMakeLists.txt
# brief: Main build file, for the project.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33				  "-mcpu=cortex-m33")
set (MCPU_CORTEX_M55				  "-mcpu=cortex-m55")
set (MCPU_CORTEX_M85				  "-mcpu=cortex-m85")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV4                        "-mfpu=vfpv4")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "EtherBench")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32H563ZITX_FLASH.ld")
set (MCPU                     "-mcpu=Cortex-M33")
set (MFPU                     "-mfpu=fpv5-sp-d16")
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")

################### CONFIGURE FLAGS ###################################
set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror -ffunction-sections -fdata-sections -g3 -O2")
set (CMAKE_CXX_FLAGS "${MCPU} -std=c++17 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror  -ffunction-sections -fdata-sections -g3 -O2")
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=EtherBench.map,--cref -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

#######################################################################

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM C CXX)

# We only add the main.c file, all the remaining is built arround libraries.
add_executable(${PROJECT_NAME} main.c)

# Add the different folders
add_subdirectory(threadx)
add_subdirectory(tasks)
add_subdirectory(hal)
add_subdirectory(bsp)

# Add libraries
# Will need to add TASKS when they're complete !
target_link_libraries(${PROJECT_NAME} HAL THREADX BSP)

# Show the user in console how much RAM and FLASH is used 
add_custom_command(TARGET EtherBench POST_BUILD
    COMMAND arm-none-eabi-size ${CMAKE_PROJECT_NAME}
    COMMAND arm-none-eabi-objdump -h -S ${CMAKE_PROJECT_NAME} > ${CMAKE_PROJECT_NAME}.list
)
