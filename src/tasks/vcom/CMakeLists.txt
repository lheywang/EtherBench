#############################################################################################################################
# file:  tasks/vcom/CMakeLists.txt
# brief: Tasks responsible for virtual com ports handling.
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/vcom.cpp
)

# Creating the library
add_library(VCOM STATIC ${SOURCES})

# Adding the include folder
target_include_directories(VCOM PUBLIC include/)