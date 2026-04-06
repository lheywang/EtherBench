# ===================================================================
# @file     CMakeLists.txt
# @brief    Just a jump file to enable add_subdirectory and
#           propagate includes
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME LIBEXTERNAL)

# Include all subfolders
add_subdirectory(third_party)

# Create the umbrella library
add_library(${LIBNAME} INTERFACE)

# Link all the sub libraries
target_link_libraries(${LIBNAME} INTERFACE
    usb-1.0
)

# On windows system, we just need to also link agains the standard libs
if(WIN32)
    target_link_libraries(${LIBNAME} INTERFACE
        setupapi
        advapi32
        winusb
    )
endif()