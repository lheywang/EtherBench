# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for athe main Window library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME libUSB)

add_library(${LIBNAME} STATIC IMPORTED GLOBAL)

set_target_properties(${LIBNAME} PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libusb-1.0.a
)

target_include_directories(${LIBNAME} INTERFACE
    {CMAKE_CURRENT_SOURCE_DIR}/include
)