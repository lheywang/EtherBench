# =================================================================================
# @file CMakeLists.txt
#
# @brief MemoryModel build file
# =================================================================================

# Create the MemoryModel library
set(SOURCES
    MemoryModel.cpp
)

qt_add_library(EtherBenchModelsMemory STATIC ${SOURCES})

target_link_libraries(EtherBenchModelsMemory PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)


target_include_directories(EtherBenchModelsMemory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)