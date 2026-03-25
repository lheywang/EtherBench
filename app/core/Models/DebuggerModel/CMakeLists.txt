# =================================================================================
# @file CMakeLists.txt
#
# @brief DebuggerModel build file
# =================================================================================

# Create the DebuggerModel library
set(SOURCES
    DebuggerModel.cpp
    DecoderModel/DecoderModel.cpp 
)

qt_add_library(EtherBenchModelsDebugger STATIC ${SOURCES})

target_link_libraries(EtherBenchModelsDebugger PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

target_include_directories(EtherBenchModelsDebugger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)