#############################################################################################################################
# file:  tasks/muxer/CMakeLists.txt
# brief: Main data router inside the project
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/muxer.cpp
)

# Creating the library
add_library(MUXER STATIC ${SOURCES})

# Adding the include folder
target_include_directories(MUXER PUBLIC include/)