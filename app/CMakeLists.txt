cmake_minimum_required(VERSION 3.16)
project(CleanQtApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)
qt_policy(SET QTP0004 OLD)

qt_add_executable(CleanQtApp
    main.cpp
    bridge/SystemController/SystemController.cpp
)

qt_add_qml_module(CleanQtApp
    URI App
    VERSION 1.0
    QML_FILES 
        qml/main.qml
        qml/components/button.qml
        qml/components/toggle.qml
        qml/views/debugger.qml
        qml/views/home.qml
        qml/views/memory.qml
        qml/views/sequences.qml
    RESOURCES
        qml/components/qmldir
        qml/views/qmldir
)

target_link_libraries(CleanQtApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)