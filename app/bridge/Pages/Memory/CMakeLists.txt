# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# Create the corresponding Page Library
set(SOURCES 
    Memory.cpp    
)

qt_add_library(EtherBenchPagesMemory STATIC 
    ${SOURCES}
)

target_include_directories(EtherBenchPagesMemory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)