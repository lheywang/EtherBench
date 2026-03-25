# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# Create the corresponding Page Library
set(SOURCES 
    Sequences.cpp    
)

qt_add_library(EtherBenchPagesSequences STATIC 
    ${SOURCES}
)

target_include_directories(EtherBenchPagesSequences PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)