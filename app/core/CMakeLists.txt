# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# First, include sub directories
add_subdirectory(Models)
add_subdirectory(IOController)

# Create the other library
set(SOURCES 
    AppCore.cpp
)

qt_add_qml_module(EtherBenchCore  
    STATIC
    URI "EtherBench.Core"
    VERSION 1.0
    SOURCES
        ${SOURCES}
)

target_link_libraries(EtherBenchCore PUBLIC
    EtherBenchModels
    EtherBenchIO
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

target_include_directories(EtherBenchCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

