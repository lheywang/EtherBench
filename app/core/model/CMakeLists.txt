# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe the global view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME libModel)

# Include all subfolders
add_subdirectory(caster)
add_subdirectory(parameter)
add_subdirectory(memory)
add_subdirectory(status)

# Create the umbrella library
add_library(${LIBNAME} INTERFACE)

# Link all the sub libraries
target_link_libraries(${LIBNAME} INTERFACE
    libParameter
    libMemory
    libStatus
    libCaster
)