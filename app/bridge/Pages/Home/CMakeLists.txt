# =================================================================================
# @file CMakeLists.txt
#
# @brief Base file for the build chain of the QT desktop application for
#        EtherBench.
# =================================================================================

# Create the corresponding Page Library
set(SOURCES 
    Home.cpp    
)

qt_add_library(EtherBenchPagesHome STATIC 
    ${SOURCES}
)

target_include_directories(EtherBenchPagesHome PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)