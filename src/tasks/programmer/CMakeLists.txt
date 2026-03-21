#############################################################################################################################
# file:  tasks/programmer/CMakeLists.txt
# brief: CMSIS programmer, in between others programming function.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_programmer.cpp
)

## Add the programming classes sources
list(APPEND SOURCES
	src/Programmer/Programmer.cpp
	src/Programmer/HardwareProbeManager/HardwareProbeManager.cpp
	src/Programmer/Probes/cJTAGProbe/cJTAGProbe.cpp
	src/Programmer/Probes/ICSPProbe/ICSPProbe.cpp
	src/Programmer/Probes/JTAGProbe/JTAGProbe.cpp
	src/Programmer/Probes/SPIProbe/SPIProbe.cpp
	src/Programmer/Probes/SWDProbe/SWDProbe.cpp

)

# Creating the library
add_library(PROGRAMMER STATIC ${SOURCES})

target_link_libraries(PROGRAMMER HAL THREADX)

# Adding the include folder
target_include_directories(PROGRAMMER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
  	${CMAKE_CURRENT_SOURCE_DIR}/CMSIS-DAP/include/
)