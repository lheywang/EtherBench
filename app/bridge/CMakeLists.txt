# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# Include other files
add_subdirectory(Pages)

# Build the library
set(SOURCES
    SystemController.cpp
)

qt_add_qml_module(EtherBenchSystem
    STATIC
    URI "EtherBench.Bridge"
    VERSION 1.0
    SOURCES
        ${SOURCES}
)

target_include_directories(EtherBenchSystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(EtherBenchSystem PUBLIC
    EtherBenchPages
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

