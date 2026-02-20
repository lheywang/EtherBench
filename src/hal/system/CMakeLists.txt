#############################################################################################################################
# file:  hal/system/CMakeLists.txt
# brief: System init build files
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	src/syscalls.c
	src/sysmem.c
)

# Creating the library
add_library(SYSTEM STATIC ${SOURCES})

# Adding the include folder (empty here)
# target_include_directories(SYSTEM PUBLIC include/)