# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for a view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(LIBNAME libMemory)

# Configure the sources
set(SOURCES
    src/memoryBuffer/memoryBuffer.cpp
    src/memoryBuffer/memoryFile.cpp
    src/memoryBuffer/memoryRam.cpp
    src/memoryBuffer/memoryCircular.cpp
    src/memoryPool.cpp
)
set(HEADERS
    include/models/memoryBuffer/memoryBuffer.hpp
    include/models/memoryBuffer/memoryFile.hpp
    include/models/memoryBuffer/memoryRam.hpp
    include/models/memoryBuffer/memoryCircular.hpp
    include/models/memoryPool.hpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# Link against the required libs
target_link_libraries(${LIBNAME} PUBLIC Qt6::Widgets)

# If testing is enabled
if(BUILD_TESTING) 
    add_subdirectory(tests)
endif()