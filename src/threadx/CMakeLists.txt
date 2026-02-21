#############################################################################################################################
# file:  threadx/CMakeLists.txt
# brief: RTOS build file
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# We only need to add the required subdirectories
add_subdirectory(threadx)
add_subdirectory(fatx)
add_subdirectory(levelx)
add_subdirectory(netxduo)
add_subdirectory(usbx)

# Creating an higher level library (to prevent from the user to link against too much libs)
add_library(THREADX INTERFACE)

target_link_libraries(THREADX INTERFACE THREADX_OS)

# ADD FATX LEVELX NETXDUO  USBX libs, when sources will be available