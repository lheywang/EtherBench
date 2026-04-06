# ===================================================================
# @file     CMakeLists.txt
# @brief    Main build file
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# -------------------------------------------------------------------
# GENERIC CONFIGURATION
# -------------------------------------------------------------------
# CMake configuration
cmake_minimum_required(VERSION 3.20)
project(EtherBenchApp LANGUAGES CXX)

# Declare options
option(BUILD_TESTING "Build unit tests" ON)

# Set C++ version used. We just use the latest.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CPpack variables
set(CMAKE_INSTALL_BINDIR ".")
set(CMAKE_INSTALL_LIBDIR ".")
set(CMAKE_INSTALL_INCLUDEDIR ".")

# Force static builds
set(BUILD_SHARED_LIBS OFF)

# Add some parameters about the config build
add_compile_options("-Wall" "-Wextra")
if(CMAKE_BUILD_TYPE==debug)
    add_compile_options("-Og" "-g3")
else()
    add_compile_options("-O3" "-g0")
endif()

# Configure testing
if(BUILD_TESTING)
    enable_testing()
    message(STATUS "Unit tests are ENABLED")
endif()

# Configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Search for Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Test)
qt_standard_project_setup()

# -------------------------------------------------------------------
# EXECUTABLE BUILD
# -------------------------------------------------------------------
# Add the different libraries
add_subdirectory(libs)
add_subdirectory(core)
add_subdirectory(main)
add_subdirectory(views)

# Configure sources files
set(SOURCES
    main.cpp
)
set(RESSOURCES
    ressources/ressources.qrc
)

# Add the main executable
qt_add_executable(${PROJECT_NAME} ${SOURCES} ${RESSOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    LIBEXTERNAL
    LIBMAIN
    LIBCORE
    LIBVIEWS

    Qt6::Widgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
)

# -------------------------------------------------------------------
# EXECUTABLE BUILD
# -------------------------------------------------------------------
if (BUILD_TESTING)
    set(TESTING_ARGS 
        --output-on-failure
        --parallel
        --progress
        --repeat-until-fail 10
        --output-log "logs.txt"
        --schedule-random
        --output-junit "report.xml"
    
    )

    add_custom_target(tests
            COMMAND 
                ${CMAKE_CTEST_COMMAND} ${TESTING_ARGS}
            WORKING_DIRECTORY 
                ${CMAKE_BINARY_DIR}
            COMMENT 
                "Running unit tests for EtherBench"
            VERBATIM
        )
endif()

# -------------------------------------------------------------------
# ADD SCRIPTS TO FETCH DEPENDENCIES
# -------------------------------------------------------------------
set(LOCAL_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../output")
set(deploy_script deploy_script)

set(EXTERNAL_LIBRARIES "")
if(WIN32)
    set(EXTERNAL_LIBRARIES "")
else()
    if(LINUX)
        set(EXTERNAL_LIBRARIES "")
    endif()
endif()

# Configure the project build procedure :
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION .
    LIBRARY DESTINATION .
    ARCHIVE DESTINATION .
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/configs/decoders
    DESTINATION . 
)
install(FILES ${EXTERNAL_DLLS} DESTINATION .)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT ${deploy_script}
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
    NO_COMPILER_RUNTIME
)

install(SCRIPT ${deploy_script})

if(WIN32)
    get_filename_component(COMPILER_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(LLVM_RUNTIME_DLLS
        "${COMPILER_DIR}/libc++.dll"
        "${COMPILER_DIR}/libunwind.dll"
    )
    install(FILES ${LLVM_RUNTIME_DLLS} DESTINATION .)
endif()

# Finally add a custom target that create the output/ folder
add_custom_target(bundle 
    COMMAND 
        ${CMAKE_COMMAND} 
            --install ${CMAKE_BINARY_DIR} 
            --prefix ${LOCAL_OUTPUT_DIR}
    COMMAND # Just delete the qt.conf file, which is not needed and can cause issues with some plugins
        ${CMAKE_COMMAND} -E rm -f ${LOCAL_OUTPUT_DIR}/qt.conf
    COMMENT 
        "Packaging app into ${LOCAL_OUTPUT_DIR}"
    DEPENDS 
        ${PROJECT_NAME}
)

add_dependencies(bundle ${PROJECT_NAME})

# -------------------------------------------------------------------
# BUILD THE INSTALLER (CPACK)
# -------------------------------------------------------------------
# Include dependencies
include(CPack)

# Configure CPack
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "EtherBenchLabs")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "EtherBench Companion App")

# Set the output type we need
if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS") # Generates a Zip AND an Installer
else()
    if(LINUX)
        set(CPACK_GENERATOR "TGZ;DEB") # Generates a .tar.gz AND a Debian package
    endif()
endif()

# Add the related custom command
add_custom_target(dist
    COMMAND 
        ${CMAKE_COMMAND}
            --build ${CMAKE_CURRENT_BINARY_DIR}
            --target package
    WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}
    COMMENT
        "Creating the installer file"
    VERBATIM
)

# Ensure the installer cannot be build without an up to date target
add_dependencies(dist ${PROJECT_NAME})
add_dependencies(dist bundle)


