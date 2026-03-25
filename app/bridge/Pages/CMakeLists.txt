# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# That's jump to all the subsequent files
add_subdirectory(Debugger)
add_subdirectory(Home)
add_subdirectory(Memory)
add_subdirectory(Sequences)

add_library(EtherBenchPages INTERFACE)

target_link_libraries(EtherBenchPages INTERFACE
    EtherBenchPagesDebugger
    EtherBenchPagesHome
    EtherBenchPagesMemory
    EtherBenchPagesSequences
)