# =================================================================================
# @file CMakeLists.txt
#
# @brief Models build file, ensure all models are built within their own library.
# =================================================================================

add_subdirectory(DebuggerModel)
add_subdirectory(MemoryModel)

add_library(EtherBenchModels INTERFACE)

target_link_libraries(EtherBenchModels INTERFACE
    EtherBenchModelsMemory
    EtherBenchModelsDebugger
)