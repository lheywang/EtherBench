cmake_minimum_required(VERSION 3.16)
project(EtherBenchApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml_imports)

add_subdirectory(third_party)

qt_add_executable(${PROJECT_NAME}
    main.cpp
    bridge/SystemController/SystemController.cpp
    bridge/Pages/Debugger/Debugger.cpp
    bridge/Pages/Home/Home.cpp
    bridge/Pages/Memory/Memory.cpp
    bridge/Pages/Sequences/Sequences.cpp
    core/AppCore.cpp
    core/IOController/CommandParser/CommandParser.cpp
    core/IOController/InterfaceController/EthernetController/EthernetController.cpp
    core/IOController/InterfaceController/USBController/USBController.cpp
    core/Models/DebuggerModel/DebuggerModel.cpp
    core/Models/DebuggerModel/DecoderModel/DecoderModel.cpp
    core/Models/MemoryModel/MemoryModel.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}       
    ${CMAKE_CURRENT_SOURCE_DIR}/bridge/SystemController
)

qt_add_qml_module(${PROJECT_NAME}
    URI App
    VERSION 1.0
    QML_FILES 
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

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    libusb
)

if(WIN32)
    # Recherche de l'outil de déploiement Qt
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT6_INSTALL_PREFIX}/bin")
    
    if(WINDEPLOYQT_EXECUTABLE)
        # Exécution automatique après chaque build réussi
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