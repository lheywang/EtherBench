cmake_minimum_required(VERSION 3.16)
project(EtherBenchApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml_imports)

add_subdirectory(qml)
add_subdirectory(third_party)

qt_add_executable(${PROJECT_NAME}
    main.cpp
    bridge/SystemController/SystemController.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI App
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES 
        qml/Main.qml
    DEPENDENCIES
        App.Views
        App.Components
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    libusb
)