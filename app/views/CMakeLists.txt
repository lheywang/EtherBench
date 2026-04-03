# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe the global view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME LIBVIEWS)

# Include all subfolders
add_subdirectory(base)
add_subdirectory(debugger)
add_subdirectory(help)
add_subdirectory(home)
add_subdirectory(io)
add_subdirectory(memory)
add_subdirectory(programmer)
add_subdirectory(sequence)
add_subdirectory(settings)

# Create the umbrella library
add_library(${LIBNAME} INTERFACE)

# Link all the sub libraries
target_link_libraries(${LIBNAME} INTERFACE
    DebuggerView
    HelpView
    HomeView
    IOView
    MemoryView
    ProgrammerView
    SequenceView
    SettingsView
)