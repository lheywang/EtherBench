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

# Configure QT
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
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
    qml/views/settings/SettingsTree.qml
    qml/views/settings/app/App.qml
    qml/views/settings/probe/Probe.qml
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

# If under Windows developpement, we just ensure all the correct DLL are placed
# alongside the executable.
if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT6_INSTALL_PREFIX}/bin")
    
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} 
                --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/qml 
                $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Deploying QT DLLs..."
        )
    else()
        message("Could not find QT deployement utility. Program may not work.")
    endif()
endif()