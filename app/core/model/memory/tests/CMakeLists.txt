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

foreach(test_source ${SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    set(target_name "test_${test_name}")

    add_executable(${target_name} ${test_source})
    target_link_libraries(${target_name} PRIVATE LIBCORE Qt6::Test)
    
    add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${target_name}>)
endforeach()