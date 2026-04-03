# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for athe main Window library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
include(FetchContent)

# Fetch the library
FetchContent_Declare(
    libusb
    GIT_REPOSITORY  https://github.com/libusb/libusb.git
    GIT_TAG         v1.0.29
)

# Configure it
set(LIBUSB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LIBUSB_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# Build it link it 
FetchContent_MakeAvailable(libusb)