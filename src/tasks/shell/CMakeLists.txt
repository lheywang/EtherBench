#############################################################################################################################
# file:  tasks/shell/CMakeLists.txt
# brief: A nice shell engine, designed to handle user inputs.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/task_shell.cpp
)

list(APPEND SOURCES
    src/ShellStream/ShellStreamBase.cpp
    src/ShellStream/ShellStreamCdc.cpp
    src/ShellStream/ShellStreamTelnet.cpp
)

list(APPEND SOURCES
    src/bridge/usb_bridge.cpp
    src/bridge/telnet_bridge.cpp
)

# Creating the library
add_library(SHELL STATIC ${SOURCES})

target_link_libraries(SHELL THREADX_OS USBX NETXDUO)

# Adding the include folder
target_include_directories(SHELL PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)