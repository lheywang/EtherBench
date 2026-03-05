#############################################################################################################################
# file:  tasks/parser/CMakeLists.txt
# brief: Main command parser build logic
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################

# Including the gperf build
find_program(
    GPERF_EXECUTABLE 
    gperf 
    REQUIRED
)

# Set sources
set(SOURCES)

# Set GPERF sources
set(
    GPERF_INPUT 
    ${CMAKE_CURRENT_SOURCE_DIR}/gperf/shell.gperf
    ${CMAKE_CURRENT_SOURCE_DIR}/gperf/scpi.gperf
)

foreach(GPERF_FILE IN LISTS GPERF_INPUT)

    # Rename the .gperf file into it's .c equivalent
    get_filename_component(
        BASE_NAME 
        ${GPERF_FILE} 
        NAME_WE
    )
    set(
        GPERF_OUTPUT 
        ${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME}.c
    )

    # Ask gperf to build it
    add_custom_command(
        OUTPUT 
            ${GPERF_OUTPUT}
        COMMAND 
            ${GPERF_EXECUTABLE}
        ARGS 
            --output-file=${GPERF_OUTPUT}
            --lookup-function-name=find_${BASE_NAME}_command
            --hash-function-name=hash_${BASE_NAME} 
            -t
            ${GPERF_FILE}
        DEPENDS 
            ${GPERF_FILE}
        COMMENT 
            "Generating perfect hash table using gperf for ${BASE_NAME}..."
    )

    # On append ce fichier à la liste des sources
    list(APPEND SOURCES
        ${GPERF_OUTPUT}
    )
endforeach()

# Add the common function sources
list(APPEND SOURCES
    src/commands/scpi/custom/actions/scpi_actions_reset.cpp
    src/commands/scpi/custom/actions/scpi_actions_set.cpp
    src/commands/scpi/custom/analog/scpi_analog_input_r.cpp
    src/commands/scpi/custom/analog/scpi_analog_output.cpp
    src/commands/scpi/custom/analog/scpi_analog_temp_r.cpp
    src/commands/scpi/custom/file/scpi_file_cd.cpp
    src/commands/scpi/custom/file/scpi_file_load.cpp
    src/commands/scpi/custom/file/scpi_file_ls.cpp
    src/commands/scpi/custom/file/scpi_file_mkdir.cpp
    src/commands/scpi/custom/file/scpi_file_pwd.cpp
    src/commands/scpi/custom/hard/scpi_hard_can.cpp
    src/commands/scpi/custom/hard/scpi_hard_can_r.cpp
    src/commands/scpi/custom/hard/scpi_hard_i2c.cpp
    src/commands/scpi/custom/hard/scpi_hard_i2c_r.cpp
    src/commands/scpi/custom/hard/scpi_hard_spi.cpp
    src/commands/scpi/custom/hard/scpi_hard_spi_r.cpp
    src/commands/scpi/custom/hard/scpi_hard_usart.cpp
    src/commands/scpi/custom/hard/scpi_hard_usart_r.cpp
    src/commands/scpi/custom/logger/scpi_log_subscribe.cpp
    src/commands/scpi/custom/logger/scpi_log_unsubscribe.cpp
    src/commands/scpi/custom/prog/scpi_prog_connect.cpp
    src/commands/scpi/custom/prog/scpi_prog_detect.cpp
    src/commands/scpi/custom/prog/scpi_prog_device.cpp
    src/commands/scpi/custom/prog/scpi_prog_flash.cpp
    src/commands/scpi/custom/prog/scpi_prog_read.cpp
    src/commands/scpi/custom/prog/scpi_prog_status.cpp
    src/commands/scpi/custom/prog/scpi_prog_verify.cpp
    src/commands/scpi/custom/sequence/scpi_seq_run.cpp
    src/commands/scpi/custom/spy/scpi_spy_can.cpp
    src/commands/scpi/custom/spy/scpi_spy_i2c.cpp
    src/commands/scpi/custom/spy/scpi_spy_spi.cpp
    src/commands/scpi/custom/spy/scpi_spy_usart.cpp
    src/commands/scpi/minimal/scpi_cls.cpp
    src/commands/scpi/minimal/scpi_ese.cpp
    src/commands/scpi/minimal/scpi_ese_r.cpp
    src/commands/scpi/minimal/scpi_esr_r.cpp
    src/commands/scpi/minimal/scpi_idn_r.cpp
    src/commands/scpi/minimal/scpi_opc.cpp
    src/commands/scpi/minimal/scpi_opc_r.cpp
    src/commands/scpi/minimal/scpi_opt.cpp
    src/commands/scpi/minimal/scpi_rst.cpp
    src/commands/scpi/minimal/scpi_sre.cpp
    src/commands/scpi/minimal/scpi_sre_r.cpp
    src/commands/scpi/minimal/scpi_stb_r.cpp
    src/commands/scpi/minimal/scpi_tst_r.cpp
    src/commands/scpi/minimal/scpi_wai.cpp
)

list(APPEND SOURCES
    src/commands/shell/custom/actions/shell_actions_reset.cpp
    src/commands/shell/custom/actions/shell_actions_set.cpp
    src/commands/shell/custom/analog/shell_analog_input_r.cpp
    src/commands/shell/custom/analog/shell_analog_output.cpp
    src/commands/shell/custom/analog/shell_analog_temp_r.cpp
    src/commands/shell/custom/hard/shell_hard_can.cpp
    src/commands/shell/custom/hard/shell_hard_can_r.cpp
    src/commands/shell/custom/hard/shell_hard_i2c.cpp
    src/commands/shell/custom/hard/shell_hard_i2c_r.cpp
    src/commands/shell/custom/hard/shell_hard_spi.cpp
    src/commands/shell/custom/hard/shell_hard_spi_r.cpp
    src/commands/shell/custom/hard/shell_hard_usart.cpp
    src/commands/shell/custom/hard/shell_hard_usart_r.cpp
    src/commands/shell/custom/logger/shell_log_subscribe.cpp
    src/commands/shell/custom/logger/shell_log_unsubscribe.cpp
    src/commands/shell/custom/prog/shell_prog_connect.cpp
    src/commands/shell/custom/prog/shell_prog_detect.cpp
    src/commands/shell/custom/prog/shell_prog_device.cpp
    src/commands/shell/custom/prog/shell_prog_flash.cpp
    src/commands/shell/custom/prog/shell_prog_read.cpp
    src/commands/shell/custom/prog/shell_prog_status.cpp
    src/commands/shell/custom/prog/shell_prog_verify.cpp
    src/commands/shell/custom/sequence/shell_seq_run.cpp
    src/commands/shell/custom/spy/shell_spy_can.cpp
    src/commands/shell/custom/spy/shell_spy_i2c.cpp
    src/commands/shell/custom/spy/shell_spy_spi.cpp
    src/commands/shell/custom/spy/shell_spy_usart.cpp
    src/commands/shell/minimal/shell_cat.cpp
    src/commands/shell/minimal/shell_cd.cpp
    src/commands/shell/minimal/shell_clear.cpp
    src/commands/shell/minimal/shell_file.cpp
    src/commands/shell/minimal/shell_ls.cpp
    src/commands/shell/minimal/shell_mkdir.cpp
    src/commands/shell/minimal/shell_mv.cpp
    src/commands/shell/minimal/shell_pwd.cpp
)

list(APPEND SOURCES
    src/task_parser.cpp
)

# Removing compilations errors from gperf
add_compile_options(-Wno-missing-field-initializers -Wno-unused-parameter)

# Creating the library
add_library(PARSER STATIC ${SOURCES})

target_link_libraries(PARSER THREADX_OS LOGGER)

# Adding the include folder
target_include_directories(PARSER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)