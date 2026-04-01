# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================
# CMake Setup
cmake_minimum_required(VERSION 3.16)
project(EtherBenchApp VERSION 1.0.0 LANGUAGES CXX)

# QML Config
set(QTP0004 NEW)
set(QTP0001 NEW)

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
    qml/theme/Theme.qml
    qml/views/DebuggerView.qml
    qml/views/HelpView.qml
    qml/views/HomeView.qml
    qml/views/InputOutputView.qml
    qml/views/MemoryView.qml
    qml/views/SequencesView.qml
    qml/views/SettingsView.qml
    qml/components/StatusETH.qml
    qml/components/StatusUSB.qml
    qml/components/ContextualMenu.qml
    qml/menus/FileMenu.qml
    qml/menus/ViewMenu.qml
    qml/menus/BuildMenu.qml
    qml/menus/DebuggerMenu.qml
    qml/menus/IOMenu.qml
    qml/menus/MemoryMenu.qml
    qml/views/debugger/DebuggerDetails.qml
    qml/views/debugger/DebuggerLogs.qml
    qml/views/settings/SettingsTree.qml
    qml/views/settings/SettingsEditor.qml
)

# Set the Theme as a special file
set_source_files_properties(qml/theme/Theme.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

# Build the app : 
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
)

qt_add_qml_module(${PROJECT_NAME}
    URI EtherBench
    VERSION 1.0
    QML_FILES 
        ${QML_SOURCES}
    ENABLE_TYPE_COMPILER
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