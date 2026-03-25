# =================================================================================
# @file CMakeLists.txt
#
# @brief Build recipe for the IOController module
# =================================================================================

# Create the IOController library
set(SOURCES
    CommandParser/CommandParser.cpp
    InterfaceController/EthernetController/EthernetController.cpp
    InterfaceController/USBController/USBController.cpp    
)

qt_add_library(EtherBenchIO STATIC ${SOURCES})

target_link_libraries(EtherBenchIO 
    EtherBenchModelsDebugger  
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

target_include_directories(EtherBenchIO PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)