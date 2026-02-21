#############################################################################################################################
# file:  threadx/threadx/CMakeLists.txt
# brief: Main RTOS Sources build
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Set sources (low level context switcher)
set(SOURCES 
	ll/src/tx_initialize_low_level.S
)

# Append sources for the common part
list(APPEND SOURCES
	common/src/tx_block_allocate.c
	common/src/tx_block_pool_cleanup.c
	common/src/tx_block_pool_create.c
	common/src/tx_block_pool_delete.c
	common/src/tx_block_pool_info_get.c
	common/src/tx_block_pool_initialize.c
	common/src/tx_block_pool_prioritize.c
	common/src/tx_block_release.c
	common/src/tx_byte_allocate.c
	common/src/tx_byte_pool_cleanup.c
	common/src/tx_byte_pool_create.c
	common/src/tx_byte_pool_delete.c
	common/src/tx_byte_pool_info_get.c
	common/src/tx_byte_pool_initialize.c
	common/src/tx_byte_pool_prioritize.c
	common/src/tx_byte_pool_search.c
	common/src/tx_byte_release.c
	common/src/txe_block_allocate.c
	common/src/txe_block_pool_create.c
	common/src/txe_block_pool_delete.c
	common/src/txe_block_pool_info_get.c
	common/src/txe_block_pool_prioritize.c
	common/src/txe_block_release.c
	common/src/txe_byte_allocate.c
	common/src/txe_byte_pool_create.c
	common/src/txe_byte_pool_delete.c
	common/src/txe_byte_pool_info_get.c
	common/src/txe_byte_pool_prioritize.c
	common/src/txe_byte_release.c
	common/src/txe_event_flags_create.c
	common/src/txe_event_flags_delete.c
	common/src/txe_event_flags_get.c
	common/src/txe_event_flags_info_get.c
	common/src/txe_event_flags_set.c
	common/src/txe_event_flags_set_notify.c
	common/src/txe_mutex_create.c
	common/src/txe_mutex_delete.c
	common/src/txe_mutex_get.c
	common/src/txe_mutex_info_get.c
	common/src/txe_mutex_prioritize.c
	common/src/txe_mutex_put.c
	common/src/txe_queue_create.c
	common/src/txe_queue_delete.c
	common/src/txe_queue_flush.c
	common/src/txe_queue_front_send.c
	common/src/txe_queue_info_get.c
	common/src/txe_queue_prioritize.c
	common/src/txe_queue_receive.c
	common/src/txe_queue_send.c
	common/src/txe_queue_send_notify.c
	common/src/txe_semaphore_ceiling_put.c
	common/src/txe_semaphore_create.c
	common/src/txe_semaphore_delete.c
	common/src/txe_semaphore_get.c
	common/src/txe_semaphore_info_get.c
	common/src/txe_semaphore_prioritize.c
	common/src/txe_semaphore_put.c
	common/src/txe_semaphore_put_notify.c
	common/src/txe_thread_create.c
	common/src/txe_thread_delete.c
	common/src/txe_thread_entry_exit_notify.c
	common/src/txe_thread_info_get.c
	common/src/txe_thread_preemption_change.c
	common/src/txe_thread_priority_change.c
	common/src/txe_thread_relinquish.c
	common/src/txe_thread_reset.c
	common/src/txe_thread_resume.c
	common/src/txe_thread_suspend.c
	common/src/txe_thread_terminate.c
	common/src/txe_thread_time_slice_change.c
	common/src/txe_thread_wait_abort.c
	common/src/txe_timer_activate.c
	common/src/txe_timer_change.c
	common/src/txe_timer_create.c
	common/src/txe_timer_deactivate.c
	common/src/txe_timer_delete.c
	common/src/txe_timer_info_get.c
	common/src/tx_event_flags_cleanup.c
	common/src/tx_event_flags_create.c
	common/src/tx_event_flags_delete.c
	common/src/tx_event_flags_get.c
	common/src/tx_event_flags_info_get.c
	common/src/tx_event_flags_initialize.c
	common/src/tx_event_flags_set.c
	common/src/tx_event_flags_set_notify.c
	common/src/tx_initialize_high_level.c
	common/src/tx_initialize_kernel_enter.c
	common/src/tx_initialize_kernel_setup.c
	common/src/tx_mutex_cleanup.c
	common/src/tx_mutex_create.c
	common/src/tx_mutex_delete.c
	common/src/tx_mutex_get.c
	common/src/tx_mutex_info_get.c
	common/src/tx_mutex_initialize.c
	common/src/tx_mutex_prioritize.c
	common/src/tx_mutex_priority_change.c
	common/src/tx_mutex_put.c
	common/src/tx_queue_cleanup.c
	common/src/tx_queue_create.c
	common/src/tx_queue_delete.c
	common/src/tx_queue_flush.c
	common/src/tx_queue_front_send.c
	common/src/tx_queue_info_get.c
	common/src/tx_queue_initialize.c
	common/src/tx_queue_prioritize.c
	common/src/tx_queue_receive.c
	common/src/tx_queue_send.c
	common/src/tx_queue_send_notify.c
	common/src/tx_semaphore_ceiling_put.c
	common/src/tx_semaphore_cleanup.c
	common/src/tx_semaphore_create.c
	common/src/tx_semaphore_delete.c
	common/src/tx_semaphore_get.c
	common/src/tx_semaphore_info_get.c
	common/src/tx_semaphore_initialize.c
	common/src/tx_semaphore_prioritize.c
	common/src/tx_semaphore_put.c
	common/src/tx_semaphore_put_notify.c
	common/src/tx_thread_create.c
	common/src/tx_thread_delete.c
	common/src/tx_thread_entry_exit_notify.c
	common/src/tx_thread_identify.c
	common/src/tx_thread_info_get.c
	common/src/tx_thread_initialize.c
	common/src/tx_thread_preemption_change.c
	common/src/tx_thread_priority_change.c
	common/src/tx_thread_relinquish.c
	common/src/tx_thread_reset.c
	common/src/tx_thread_resume.c
	common/src/tx_thread_shell_entry.c
	common/src/tx_thread_sleep.c
	common/src/tx_thread_stack_analyze.c
	common/src/tx_thread_stack_error_handler.c
	common/src/tx_thread_stack_error_notify.c
	common/src/tx_thread_suspend.c
	common/src/tx_thread_system_preempt_check.c
	common/src/tx_thread_system_resume.c
	common/src/tx_thread_system_suspend.c
	common/src/tx_thread_terminate.c
	common/src/tx_thread_timeout.c
	common/src/tx_thread_time_slice.c
	common/src/tx_thread_time_slice_change.c
	common/src/tx_thread_wait_abort.c
	common/src/tx_time_get.c
	common/src/tx_timer_activate.c
	common/src/tx_timer_change.c
	common/src/tx_timer_create.c
	common/src/tx_timer_deactivate.c
	common/src/tx_timer_delete.c
	common/src/tx_timer_expiration_process.c
	common/src/tx_timer_info_get.c
	common/src/tx_timer_initialize.c
	common/src/tx_timer_system_activate.c
	common/src/tx_timer_system_deactivate.c
	common/src/tx_timer_thread_entry.c
	common/src/tx_time_set.c
)

# Adding the ports for the cortex M33 we use
list(APPEND SOURCES
	ports/cortex_m33/gnu/src/tx_thread_context_restore.S
	ports/cortex_m33/gnu/src/tx_thread_context_save.S
	ports/cortex_m33/gnu/src/tx_thread_interrupt_control.S
	ports/cortex_m33/gnu/src/tx_thread_interrupt_disable.S
	ports/cortex_m33/gnu/src/tx_thread_interrupt_restore.S
	ports/cortex_m33/gnu/src/tx_thread_schedule.S
	ports/cortex_m33/gnu/src/tx_thread_stack_build.S
	ports/cortex_m33/gnu/src/tx_thread_system_return.S
	ports/cortex_m33/gnu/src/tx_timer_interrupt.S
)

list(APPEND SOURCES
	app/src/app_azure_rtos.c
	app/src/app_threadx.c
)

# Creating the library
add_library(THREADX_OS STATIC ${SOURCES})

# Ensure we build against the HAL
target_link_libraries(THREADX_OS HAL LAUNCHER)

# Adding the include folder
target_include_directories(THREADX_OS PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/ports/cortex_m33/gnu/include
	${CMAKE_CURRENT_SOURCE_DIR}/common/include
	${CMAKE_CURRENT_SOURCE_DIR}/app/include
)

