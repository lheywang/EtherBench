# ===================================================================
# @file     CMakeLists.txt
# @brief    Just a jump file to enable add_subdirectory and
#           propagate includes
#
# @author   l.heywang <leonard.heywang@proton.me>
# @date     2026-04-01
# 
# ===================================================================

# Just include all sub libraries
add_subdirectory(LIEF)
add_subdirectory(libcintelhex)

# An error occured in this module, so just remove the faulty warning
add_compile_options(-Wno-pragma-pack)
add_subdirectory(libusb-cmake)