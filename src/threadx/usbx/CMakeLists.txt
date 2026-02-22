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
	common/src/ux_device_stack_alternate_setting_get.c
	common/src/ux_device_stack_alternate_setting_set.c
	common/src/ux_device_stack_class_register.c
	common/src/ux_device_stack_class_unregister.c
	common/src/ux_device_stack_clear_feature.c
	common/src/ux_device_stack_configuration_get.c
	common/src/ux_device_stack_configuration_set.c
	common/src/ux_device_stack_control_request_process.c
	common/src/ux_device_stack_descriptor_send.c
	common/src/ux_device_stack_disconnect.c
	common/src/ux_device_stack_endpoint_stall.c
	common/src/ux_device_stack_get_status.c
	common/src/ux_device_stack_host_wakeup.c
	common/src/ux_device_stack_initialize.c
	common/src/ux_device_stack_interface_delete.c
	common/src/ux_device_stack_interface_get.c
	common/src/ux_device_stack_interface_set.c
	common/src/ux_device_stack_interface_start.c
	common/src/ux_device_stack_microsoft_extension_register.c
	common/src/ux_device_stack_set_feature.c
	common/src/ux_device_stack_transfer_abort.c
	common/src/ux_device_stack_transfer_all_request_abort.c
	common/src/ux_device_stack_transfer_request.c
	common/src/ux_device_stack_uninitialize.c
	common/src/ux_system_error_handler.c
	common/src/ux_system_initialize.c
	common/src/ux_system_uninitialize.c
	common/src/ux_utility_debug_callback_register.c
	common/src/ux_utility_debug_log.c
	common/src/ux_utility_delay_ms.c
	common/src/ux_utility_descriptor_pack.c
	common/src/ux_utility_descriptor_parse.c
	common/src/ux_utility_error_callback_register.c
	common/src/ux_utility_event_flags_create.c
	common/src/ux_utility_event_flags_delete.c
	common/src/ux_utility_event_flags_get.c
	common/src/ux_utility_event_flags_set.c
	common/src/ux_utility_long_get_big_endian.c
	common/src/ux_utility_long_get.c
	common/src/ux_utility_long_put_big_endian.c
	common/src/ux_utility_long_put.c
	common/src/ux_utility_memory_allocate_add_safe.c
	common/src/ux_utility_memory_allocate.c
	common/src/ux_utility_memory_allocate_mulc_safe.c
	common/src/ux_utility_memory_allocate_mulv_safe.c
	common/src/ux_utility_memory_byte_pool_create.c
	common/src/ux_utility_memory_byte_pool_search.c
	common/src/ux_utility_memory_compare.c
	common/src/ux_utility_memory_copy.c
	common/src/ux_utility_memory_free.c
	common/src/ux_utility_memory_set.c
	common/src/ux_utility_mutex_create.c
	common/src/ux_utility_mutex_delete.c
	common/src/ux_utility_mutex_off.c
	common/src/ux_utility_mutex_on.c
	common/src/ux_utility_pci_class_scan.c
	common/src/ux_utility_pci_read.c
	common/src/ux_utility_pci_write.c
	common/src/ux_utility_physical_address.c
	common/src/ux_utility_semaphore_create.c
	common/src/ux_utility_semaphore_delete.c
	common/src/ux_utility_semaphore_get.c
	common/src/ux_utility_semaphore_put.c
	common/src/ux_utility_set_interrupt_handler.c
	common/src/ux_utility_short_get_big_endian.c
	common/src/ux_utility_short_get.c
	common/src/ux_utility_short_put_big_endian.c
	common/src/ux_utility_short_put.c
	common/src/ux_utility_string_length_check.c
	common/src/ux_utility_string_length_get.c
	common/src/ux_utility_string_to_unicode.c
	common/src/ux_utility_thread_create.c
	common/src/ux_utility_thread_delete.c
	common/src/ux_utility_thread_identify.c
	common/src/ux_utility_thread_relinquish.c
	common/src/ux_utility_thread_resume.c
	common/src/ux_utility_thread_schedule_other.c
	common/src/ux_utility_thread_sleep.c
	common/src/ux_utility_thread_suspend.c
	common/src/ux_utility_timer_create.c
	common/src/ux_utility_timer_delete.c
	common/src/ux_utility_unicode_to_string.c
	common/src/ux_utility_virtual_address.c
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
	descriptors/src/device/device_descriptor.c
	descriptors/src/configuration/debugger.c
	descriptors/src/configuration/storage.c
	descriptors/src/configuration/vcom_serial.c
	descriptors/src/configuration/vcom_terminal.c
)

# Creating the library
add_library(USBX STATIC ${SOURCES})

# Link against the OS kernel
target_link_libraries(USBX HAL THREADX_OS)

# Adding the include folder
target_include_directories(USBX PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/app/include
	${CMAKE_CURRENT_SOURCE_DIR}/common/include
	${CMAKE_CURRENT_SOURCE_DIR}/ll/include
	${CMAKE_CURRENT_SOURCE_DIR}/ports/generic/include
)
	