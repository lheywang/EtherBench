# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe the global view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME libServices)

# Include all subfolders
add_subdirectory(dataCast)

# Create the umbrella library
add_library(${LIBNAME} INTERFACE)

# Link all the sub libraries
target_link_libraries(${LIBNAME} INTERFACE
    libDataCast
)