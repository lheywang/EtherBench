#############################################################################################################################
# file:  tasks/leds/CMakeLists.txt
# brief: Task executed to control leds IO.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Search python
find_package(
    Python3
    REQUIRED 
    COMPONENTS 
    Interpreter
)

# ===============================================
# FIRST : PARAMETERS
# ===============================================
set(SCRIPT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/scripts")
set(SCRIPT_CFG "${CMAKE_CURRENT_SOURCE_DIR}/config")

set(GEN_SCRIPT    "${SCRIPT_DIR}/generate_gamma_lut.py")
set(GEN_CONFIG    "${SCRIPT_CFG}/gamma_lut.toml")

set(LUT_TARGET    "${CMAKE_CURRENT_BINARY_DIR}/gamma_lut.h")

# ===============================================
# SECOND : TOML 2 GPERF
# ===============================================
add_custom_command(
    OUTPUT
        ${LUT_TARGET}
    COMMAND
        Python3::Interpreter
        ${GEN_SCRIPT}
        --cfgfile   ${GEN_CONFIG}
        --outfile   ${LUT_TARGET}
    DEPENDS
        ${GEN_SCRIPT}
        ${GEN_CONFIG}
    COMMENT
        "Generating gamma lut correction table ${LUT_TARGET}"
    VERBATIM
)

# ===============================================
# THIRD : STANDARD C / C++ WORKFLOW
# ===============================================
# Set sources
set(SOURCES 
	src/task_leds.cpp
)

list(APPEND SOURCES
    src/Leds/LedsBase.cpp
    src/Leds/LedsWS2812.cpp
)

# Creating the library
add_library(LEDS STATIC ${SOURCES} ${LUT_TARGET})

# Link against the right libraries
target_link_libraries(LEDS THREADX HAL)

# Adding the include folder
target_include_directories(LEDS PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)
