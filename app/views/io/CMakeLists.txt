# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for a view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME IOView)

# Configure the sources
set(SOURCES
    src/ioView.cpp   
)

# Create the library
add_library(${LIBNAME} STATIC)
target_sources(${LIBNAME} PRIVATE
    ${SOURCES}
)

# Add the include directory. Since it's named views, we can just do #include "views/settingsViews.hpp" 
# even when the header is located within it's dedicated space here.
target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# Link against the required libs
target_link_libraries(${LIBNAME} PUBLIC Qt6::Widgets CORELIB)