#############################################################################################################################
# file:  threadx/usbx/CMakeLists.txt
# brief: USBX stack build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources (app)
set(SOURCES 
	app/src/app_usbx_device.c
)

# Common USBX core
list(APPEND SOURCES
	common/core/src/ux_device_stack_alternate_setting_get.c
	common/core/src/ux_device_stack_alternate_setting_set.c
	common/core/src/ux_device_stack_class_register.c
	common/core/src/ux_device_stack_class_unregister.c
	common/core/src/ux_device_stack_clear_feature.c
	common/core/src/ux_device_stack_configuration_get.c
	common/core/src/ux_device_stack_configuration_set.c
	common/core/src/ux_device_stack_control_request_process.c
	common/core/src/ux_device_stack_descriptor_send.c
	common/core/src/ux_device_stack_disconnect.c
	common/core/src/ux_device_stack_endpoint_stall.c
	common/core/src/ux_device_stack_get_status.c
	common/core/src/ux_device_stack_host_wakeup.c
	common/core/src/ux_device_stack_initialize.c
	common/core/src/ux_device_stack_interface_delete.c
	common/core/src/ux_device_stack_interface_get.c
	common/core/src/ux_device_stack_interface_set.c
	common/core/src/ux_device_stack_interface_start.c
	common/core/src/ux_device_stack_microsoft_extension_register.c
	common/core/src/ux_device_stack_set_feature.c
	common/core/src/ux_device_stack_transfer_abort.c
	common/core/src/ux_device_stack_transfer_all_request_abort.c
	common/core/src/ux_device_stack_transfer_request.c
	common/core/src/ux_device_stack_uninitialize.c
	common/core/src/ux_system_error_handler.c
	common/core/src/ux_system_initialize.c
	common/core/src/ux_system_uninitialize.c
	common/core/src/ux_utility_debug_callback_register.c
	common/core/src/ux_utility_debug_log.c
	common/core/src/ux_utility_delay_ms.c
	common/core/src/ux_utility_descriptor_pack.c
	common/core/src/ux_utility_descriptor_parse.c
	common/core/src/ux_utility_error_callback_register.c
	common/core/src/ux_utility_event_flags_create.c
	common/core/src/ux_utility_event_flags_delete.c
	common/core/src/ux_utility_event_flags_get.c
	common/core/src/ux_utility_event_flags_set.c
	common/core/src/ux_utility_long_get_big_endian.c
	common/core/src/ux_utility_long_get.c
	common/core/src/ux_utility_long_put_big_endian.c
	common/core/src/ux_utility_long_put.c
	common/core/src/ux_utility_memory_allocate_add_safe.c
	common/core/src/ux_utility_memory_allocate.c
	common/core/src/ux_utility_memory_allocate_mulc_safe.c
	common/core/src/ux_utility_memory_allocate_mulv_safe.c
	common/core/src/ux_utility_memory_byte_pool_create.c
	common/core/src/ux_utility_memory_byte_pool_search.c
	common/core/src/ux_utility_memory_compare.c
	common/core/src/ux_utility_memory_copy.c
	common/core/src/ux_utility_memory_free.c
	common/core/src/ux_utility_memory_set.c
	common/core/src/ux_utility_mutex_create.c
	common/core/src/ux_utility_mutex_delete.c
	common/core/src/ux_utility_mutex_off.c
	common/core/src/ux_utility_mutex_on.c
	common/core/src/ux_utility_pci_class_scan.c
	common/core/src/ux_utility_pci_read.c
	common/core/src/ux_utility_pci_write.c
	common/core/src/ux_utility_physical_address.c
	common/core/src/ux_utility_semaphore_create.c
	common/core/src/ux_utility_semaphore_delete.c
	common/core/src/ux_utility_semaphore_get.c
	common/core/src/ux_utility_semaphore_put.c
	common/core/src/ux_utility_set_interrupt_handler.c
	common/core/src/ux_utility_short_get_big_endian.c
	common/core/src/ux_utility_short_get.c
	common/core/src/ux_utility_short_put_big_endian.c
	common/core/src/ux_utility_short_put.c
	common/core/src/ux_utility_string_length_check.c
	common/core/src/ux_utility_string_length_get.c
	common/core/src/ux_utility_string_to_unicode.c
	common/core/src/ux_utility_thread_create.c
	common/core/src/ux_utility_thread_delete.c
	common/core/src/ux_utility_thread_identify.c
	common/core/src/ux_utility_thread_relinquish.c
	common/core/src/ux_utility_thread_resume.c
	common/core/src/ux_utility_thread_schedule_other.c
	common/core/src/ux_utility_thread_sleep.c
	common/core/src/ux_utility_thread_suspend.c
	common/core/src/ux_utility_timer_create.c
	common/core/src/ux_utility_timer_delete.c
	common/core/src/ux_utility_unicode_to_string.c
	common/core/src/ux_utility_virtual_address.c
)

list(APPEND SOURCES
	common/classes/src/ux_device_class_cdc_acm_activate.c
	common/classes/src/ux_device_class_cdc_acm_bulkin_thread.c
	common/classes/src/ux_device_class_cdc_acm_bulkout_thread.c
	common/classes/src/ux_device_class_cdc_acm_control_request.c
	common/classes/src/ux_device_class_cdc_acm_deactivate.c
	common/classes/src/ux_device_class_cdc_acm_entry.c
	common/classes/src/ux_device_class_cdc_acm_initialize.c
	common/classes/src/ux_device_class_cdc_acm_ioctl.c
	common/classes/src/ux_device_class_cdc_acm_read.c
	common/classes/src/ux_device_class_cdc_acm_unitialize.c
	common/classes/src/ux_device_class_cdc_acm_write.c
	common/classes/src/ux_device_class_cdc_acm_write_with_callback.c
	common/classes/src/ux_device_class_storage_activate.c
	common/classes/src/ux_device_class_storage_control_request.c
	common/classes/src/ux_device_class_storage_csw_send.c
	common/classes/src/ux_device_class_storage_deactivate.c
	common/classes/src/ux_device_class_storage_entry.c
	common/classes/src/ux_device_class_storage_format.c
	common/classes/src/ux_device_class_storage_get_configuration.c
	common/classes/src/ux_device_class_storage_get_performance.c
	common/classes/src/ux_device_class_storage_get_status_notification.c
	common/classes/src/ux_device_class_storage_initialize.c
	common/classes/src/ux_device_class_storage_inquiry.c
	common/classes/src/ux_device_class_storage_mode_select.c
	common/classes/src/ux_device_class_storage_mode_sense.c
	common/classes/src/ux_device_class_storage_prevent_allow_media_removal.c
	common/classes/src/ux_device_class_storage_read.c
	common/classes/src/ux_device_class_storage_read_capacity.c
	common/classes/src/ux_device_class_storage_read_disk_information.c
	common/classes/src/ux_device_class_storage_read_dvd_structure.c
	common/classes/src/ux_device_class_storage_read_format_capacity.c
	common/classes/src/ux_device_class_storage_read_toc.c
	common/classes/src/ux_device_class_storage_report_key.c
	common/classes/src/ux_device_class_storage_request_sense.c
	common/classes/src/ux_device_class_storage_start_stop.c
	common/classes/src/ux_device_class_storage_synchronize_cache.c
	common/classes/src/ux_device_class_storage_test_ready.c
	common/classes/src/ux_device_class_storage_thread.c
	common/classes/src/ux_device_class_storage_uninitialize.c
	common/classes/src/ux_device_class_storage_verify.c
	common/classes/src/ux_device_class_storage_write.c
)

list(APPEND SOURCES
	ll/src/ux_dcd_stm32_callback.c
	ll/src/ux_dcd_stm32_endpoint_create.c
	ll/src/ux_dcd_stm32_endpoint_destroy.c
	ll/src/ux_dcd_stm32_endpoint_reset.c
	ll/src/ux_dcd_stm32_endpoint_stall.c
	ll/src/ux_dcd_stm32_endpoint_status.c
	ll/src/ux_dcd_stm32_frame_number_get.c
	ll/src/ux_dcd_stm32_function.c
	ll/src/ux_dcd_stm32_initialize.c
	ll/src/ux_dcd_stm32_initialize_complete.c
	ll/src/ux_dcd_stm32_interrupt_handler.c
	ll/src/ux_dcd_stm32_transfer_abort.c
	ll/src/ux_dcd_stm32_transfer_request.c
	ll/src/ux_dcd_stm32_transfer_run.c
	ll/src/ux_dcd_stm32_uninitialize.c
)

list(APPEND SOURCES
	descriptors/src/descriptor.c
)

list(APPEND SOURCES
	dummy/src/ux_dummy.c
)

# Creating the library
add_library(USBX STATIC ${SOURCES})

# Link against the OS kernel
target_link_libraries(USBX ST_HAL THREADX_OS)

# Adding the include folder
target_include_directories(USBX PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/app/include
	${CMAKE_CURRENT_SOURCE_DIR}/common/core/include
	${CMAKE_CURRENT_SOURCE_DIR}/common/classes/include
	${CMAKE_CURRENT_SOURCE_DIR}/ll/include
	${CMAKE_CURRENT_SOURCE_DIR}/ports/generic/include
	${CMAKE_CURRENT_SOURCE_DIR}/descriptors/include
	${CMAKE_CURRENT_SOURCE_DIR}/dummy/include
)
	