# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# Create the corresponding Page Library
set(SOURCES 
    Debugger.cpp    
)

qt_add_library(EtherBenchPagesDebugger STATIC 
    ${SOURCES}
)

target_include_directories(EtherBenchPagesDebugger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

