# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for an external library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME libcintelhex)

# Configure the sources
set(SOURCES
    libcintelhex/src/ihex_copy.c
    libcintelhex/src/ihex_parse.c
    libcintelhex/src/ihex_record.c
)
set(HEADERS
    libcintelhex/include/cintelhex.h
)

# Create the library
add_library(${LIBNAME} STATIC)
target_sources(${LIBNAME} PRIVATE
    ${SOURCES}
    ${HEADERS}
)

# Add the include directory. Since it's named views, we can just do #include "views/settingsViews.hpp" 
# even when the header is located within it's dedicated space here.
target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libcintelhex/include/
)
target_include_directories(${LIBNAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link against the required libs
target_link_libraries(${LIBNAME} PUBLIC Qt6::Widgets)