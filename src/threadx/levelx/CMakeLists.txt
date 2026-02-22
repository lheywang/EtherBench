#############################################################################################################################
# file:  threadx/levelx/CMakeLists.txt
# brief: LevelX file system build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources
set(SOURCES 
	common/src/lx_nand_flash_256byte_ecc_check.c
	common/src/lx_nand_flash_256byte_ecc_compute.c
	common/src/lx_nand_flash_block_allocate.c
	common/src/lx_nand_flash_block_data_move.c
	common/src/lx_nand_flash_block_find.c
	common/src/lx_nand_flash_block_mapping_set.c
	common/src/lx_nand_flash_block_status_set.c
	common/src/lx_nand_flash_close.c
	common/src/lx_nand_flash_data_page_copy.c
	common/src/lx_nand_flash_defragment.c
	common/src/lx_nand_flash_driver_block_erase.c
	common/src/lx_nand_flash_driver_block_erased_verify.c
	common/src/lx_nand_flash_driver_block_status_get.c
	common/src/lx_nand_flash_driver_block_status_set.c
	common/src/lx_nand_flash_driver_page_erased_verify.c
	common/src/lx_nand_flash_erase_count_set.c
	common/src/lx_nand_flash_extended_cache_enable.c
	common/src/lx_nand_flash_format.c
	common/src/lx_nand_flash_free_block_list_add.c
	common/src/lx_nand_flash_initialize.c
	common/src/lx_nand_flash_mapped_block_list_add.c
	common/src/lx_nand_flash_mapped_block_list_get.c
	common/src/lx_nand_flash_mapped_block_list_remove.c
	common/src/lx_nand_flash_memory_initialize.c
	common/src/lx_nand_flash_metadata_allocate.c
	common/src/lx_nand_flash_metadata_build.c
	common/src/lx_nand_flash_metadata_write.c
	common/src/lx_nand_flash_open.c
	common/src/lx_nand_flash_page_ecc_check.c
	common/src/lx_nand_flash_page_ecc_compute.c
	common/src/lx_nand_flash_partial_defragment.c
	common/src/lx_nand_flash_sectors_read.c
	common/src/lx_nand_flash_sectors_release.c
	common/src/lx_nand_flash_sectors_write.c
	common/src/lx_nand_flash_sector_read.c
	common/src/lx_nand_flash_sector_release.c
	common/src/lx_nand_flash_sector_write.c
	common/src/lx_nand_flash_system_error.c
)

# Creating the library
add_library(LEVELX STATIC ${SOURCES})

# Link against the correct libraries
target_link_libraries(LEVELX HAL THREADX_OS)

# Adding the include folder
target_include_directories(LEVELX PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/common/include/
	${CMAKE_CURRENT_SOURCE_DIR}/app/include/
)