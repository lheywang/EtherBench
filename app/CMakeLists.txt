# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================
# CMake Setup
cmake_minimum_required(VERSION 3.16)
project(EtherBenchApp VERSION 1.0.0 LANGUAGES CXX)

# Project Setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_BINDIR ".")
set(CMAKE_INSTALL_LIBDIR ".")
set(CMAKE_INSTALL_INCLUDEDIR ".")

# Configure QT
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets)
qt_standard_project_setup(REQUIRES 6.5)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml_imports)

# Include sub directories
add_subdirectory(third_party)
add_subdirectory(core)
add_subdirectory(bridge)


set(SOURCES
    main.cpp
)

set(QML_SOURCES 
    qml/Main.qml
    qml/views/Debugger.qml
    qml/views/Help.qml
    qml/views/Home.qml
    qml/views/InputOutput.qml
    qml/views/Memory.qml
    qml/views/Sequences.qml
    qml/views/Settings.qml
    qml/components/StatusETH.qml
    qml/components/StatusUSB.qml
    qml/components/ContextualMenu.qml
    qml/menus/File.qml
    qml/menus/View.qml
    qml/menus/Build.qml
    qml/menus/Debugger.qml
    qml/menus/IO.qml
    qml/menus/Memory.qml
    qml/views/debugger/Details.qml
    qml/views/debugger/Logs.qml
    qml/views/settings/Tree.qml
    qml/views/settings/Editor.qml
)

# Build the app : 
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
)

qt_add_qml_module(${PROJECT_NAME}
    URI App
    VERSION 1.0
    QML_FILES 
        ${QML_SOURCES}
    SOURCES
        ${SOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    libusb
    EtherBenchCore
    EtherBenchSystem
)

# Finally, package the app into an output/ folder : 
set(LOCAL_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../output")

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
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/settings/
    DESTINATION .   
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/decoders
    DESTINATION .    
)

install(FILES ${EXTERNAL_DLLS} DESTINATION .)

set(QT_DEPLOY_OPTIONS "--compiler-runtime" "--no-translations")
qt_generate_deploy_qml_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    DEPLOY_TOOL_OPTIONS ${QT_DEPLOY_OPTIONS}
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

# Configure CPack : 
include(CPack)

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "EtherBenchLabs")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "EtherBench Companion App")

if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS") # Generates a Zip AND an Installer
else()
    if(LINUX)
        set(CPACK_GENERATOR "TGZ;DEB") # Generates a .tar.gz AND a Debian package
    endif()
endif()

# To conclude, add a custom dist command
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

add_dependencies(dist bundle)
add_dependencies(dist ${PROJECT_NAME})