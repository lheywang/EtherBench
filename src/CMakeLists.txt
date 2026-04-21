#############################################################################################################################
# file:  CMakeLists.txt
# brief: Main build file, for the project.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################


# ==============================================================================
# DOCUMENTATION (DOXYGEN)
# ==============================================================================
# Finding tools
find_package(Doxygen)

if(DOXYGEN_FOUND)

    # Fetch dot (will ensure that the build WILL work)
    find_program(
        DOT_EXECUTABLE 
        NAMES dot
        DOC "Path to Graphviz dot executable"
    )

    if(NOT DOT_EXECUTABLE)
        message(WARNING "Graphviz (dot.exe) was not found. Errors may occurs when generating the doc.")
    else()
        get_filename_component(DOT_PATH_DIR "${DOT_EXECUTABLE}" DIRECTORY)
    endif()

    include(FetchContent)
    FetchContent_Declare(
        doxygen-awesome-css
        URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP  TRUE
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)

    # Configure some variables here and here
    set(AWESOME_CSS_DIR ${doxygen-awesome-css_SOURCE_DIR})

    set(DOXYFILE_IN   ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT  ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc")
    file(MAKE_DIRECTORY "${DOXYGEN_OUTPUT_DIR}")

    set(DOXYGEN_HTML_ADDON ${CMAKE_CURRENT_SOURCE_DIR}/doc/html/)
    set(DOXYGEN_CSS_ADDON ${CMAKE_CURRENT_SOURCE_DIR}/doc/css/)
    set(DOXYGEN_XML_ADDON ${CMAKE_CURRENT_SOURCE_DIR}/doc/xml/)
    set(DOXYGEN_IMAGES_ADDON ${CMAKE_CURRENT_SOURCE_DIR}/doc/images/)
    set(DOXYGEN_MARKDOWN_ADDON ${CMAKE_CURRENT_SOURCE_DIR}/doc/markdown/)

    set(DOXYGEN_ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

    # Configure the file
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    # Add the doc target
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Génération de la documentation Doxygen..."
        VERBATIM
    )
else()
    message(WARNING "Could not find Doxygen. Documentation won't be available.")
endif()

# ==============================================================================
# TESTS (GOOGLE TEST)
# ==============================================================================
option(BUILD_TESTING "Build unit tests (Host only)" OFF)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL                         https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP  TRUE
    )
    # GTest force parfois l'installation, on la désactive pour rester propre
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    enable_testing()
endif()

# ==============================================================================
# STANDARD BUILD
# ==============================================================================
cmake_minimum_required(VERSION 3.20)
project("EtherBench")
enable_language(ASM C CXX)

# We just need to configure variables
add_compile_definitions(
	-DUSE_HAL_DRIVER 
	-DSTM32H563xx
	-DTX_SINGLE_MODE_NON_SECURE
	-DTX_INCLUDE_USER_DEFINE_FILE 
	-DUX_INCLUDE_USER_DEFINE_FILE
    -DLX_INCLUDE_USER_DEFINE_FILE
    -DFX_INCLUDE_USER_DEFINE_FILE
    -DLX_NAND_FLASH_SECTOR_MAPPING_CACHE_SIZE=1024
    -DLX_NAND_ENABLE
	-D$<$<CONFIG:Debug>:DEBUG>
    -DFX_ENABLE_EXFAT
    -DFX_MAX_LONG_NAME_LEN=256
)

add_compile_options(
    -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/= 
)

# Add the config directory, which is global
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/
    ${CMAKE_CURRENT_SOURCE_DIR}/interrupts/include/
)

# We only add the main.c file, all the remaining is built arround libraries.
set(SOURCES
    main.c
    startup/startup_stm32h563zitx.s
    startup/system_stm32h5xx.c
    interrupts/src/it.c
    interrupts/src/error_handler.c
    interrupts/src/hal_it.c
    interrupts/src/stm32h5xx_it.c
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Add the different folders (Vendor and RTOS ones)
add_subdirectory(hal)
add_subdirectory(bsp)
add_subdirectory(threadx)

# Add the user builds (with a new flag, to ensure code quality)
add_compile_options(-Wextra)
add_subdirectory(tasks)
add_subdirectory(launcher)

# Add libraries
# Will need to add TASKS when they're complete !
target_link_libraries(${PROJECT_NAME} 
    -Wl,--start-group
	THREADX
	TASKS
	LAUNCHER
    BSP
    HAL
    -Wl,--end-group 
)

