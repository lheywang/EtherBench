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

# Set C++ version used. We just use the latest.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CPpack variables
set(CMAKE_INSTALL_BINDIR ".")
set(CMAKE_INSTALL_LIBDIR ".")
set(CMAKE_INSTALL_INCLUDEDIR ".")

# Force static builds
set(BUILD_SHARED_LIBS OFF)

# Configuring the linking, depending on the target platform
if(WIN32)
    add_link_options("-static" "-static-libgcc" "-static-libstdc++")
    message("Linking the libGCC statically, because you're on a Windows platform.")
endif()

# Configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Search for Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

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

# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})
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
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/configs/settings/
    DESTINATION .   
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/configs/decoders
    DESTINATION ./decoders/ 
)
install(FILES ${EXTERNAL_DLLS} DESTINATION .)

set(QT_DEPLOY_OPTIONS "--compiler-runtime" "--no-translations")
qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT ${deploy_script}
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

# Finally add a custom target that create the output/ folder
add_custom_target(bundle 
    COMMAND 
        ${CMAKE_COMMAND} 
            --install ${CMAKE_BINARY_DIR} 
            --prefix ${LOCAL_OUTPUT_DIR}
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


