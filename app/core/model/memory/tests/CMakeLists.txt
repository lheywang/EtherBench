# ===================================================================
# @file     CMakeLists.txt
# @brief    Build recipe for a view library
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Set lib name
set(TESTNAME testMemory)

# Configure the sources
set(SOURCES
    src/memoryTest.cpp
    src/memoryTest2.cpp
)

# Fetch some paths by defaults
get_target_property(QT_BIN_DIR Qt6::Core LOCATION)
get_filename_component(QT_BIN_DIR "${QT_BIN_DIR}" DIRECTORY)
get_filename_component(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

# Iterate over the list of sources, and create an executable for each of them.
# For each, we add a test named after it's file name, and with set it's own path to a value, 
# to ensure Windows will find the DLL.
foreach(test_source ${SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    set(target_name "test_${test_name}")

    add_executable(${target_name} ${test_source})
    target_link_libraries(${target_name} PRIVATE LIBCORE Qt6::Test)

    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${target_name}>)

    if (WIN32)
        set_tests_properties(${test_name} PROPERTIES ENVIRONMENT 
            "PATH=${QT_BIN_DIR};${COMPILER_BIN_DIR};$ENV{PATH}"
        )
    endif()
endforeach()