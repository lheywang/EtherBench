#############################################################################################################################
# file:  tasks/parser/CMakeLists.txt
# brief: Main command parser build logic
# 
# author : l.heywang <leonard.heywang@proton.me>
# date : 20/02/2026
#############################################################################################################################
# Search for gperf
find_program(
    GPERF_EXECUTABLE 
    gperf 
    REQUIRED
)

# Search for Python
find_package(
    Python3
    REQUIRED 
    COMPONENTS 
    Interpreter
)

# ===============================================
# FIRST : PARAMETERS
# ===============================================
set(CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")
set(SCRIPT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

set(COMMANDS_TOML "${CONFIG_DIR}/commands.toml")
set(GEN_SCRIPT    "${SCRIPT_DIR}/generate_gperf.py")

set(SCPI_GPERF    "${CMAKE_CURRENT_BINARY_DIR}/scpi.gperf")
set(SHELL_GPERF   "${CMAKE_CURRENT_BINARY_DIR}/shell.gperf")
set(ARGS_GPERF    "${CMAKE_CURRENT_SOURCE_DIR}/gperf/keywords.gperf")

# Set sources list
set(SOURCES)

# ===============================================
# SECOND : TOML 2 GPERF
# ===============================================
add_custom_command(
    OUTPUT
        ${SCPI_GPERF}
        ${SHELL_GPERF}
    COMMAND
        Python3::Interpreter
        ${GEN_SCRIPT}
        --input     ${COMMANDS_TOML}
        --out-scpi  ${SCPI_GPERF}
        --out-shell ${SHELL_GPERF}
    DEPENDS
        ${COMMANDS_TOML}
        ${GEN_SCRIPT}
    COMMENT
        "Generating .gperf tables from TOML definition..."
    VERBATIM
)

# ===============================================
# SECOND : GPERF 2 C
# ===============================================

# Set GPERF sources
set(GPERF_FILES 
    ${SCPI_GPERF} 
    ${SHELL_GPERF}    
)

foreach(GPERF_FILE IN LISTS GPERF_FILES)

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
            -t
            -C
            -D
            -G
            -L C
            -S 1
            -N find_${BASE_NAME}_command
            -H hash_${BASE_NAME}
            --output-file=${GPERF_OUTPUT}
            ${GPERF_FILE}
        DEPENDS 
            ${GPERF_FILE}
        COMMENT 
            "Compiling perfect hash table: ${BASENAME}.gperf -> .c"
        VERBATIM
    )

    # On append ce fichier à la liste des sources
    list(APPEND SOURCES
        ${GPERF_OUTPUT}
    )
endforeach()

set(GPERF_FILES 
    ${ARGS_GPERF} 
)

foreach(GPERF_FILE IN LISTS GPERF_FILES)

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
            -C
            -D
            -G
            -L C
            -S 1
            -N find_${BASE_NAME}_command
            -H hash_${BASE_NAME}
            --output-file=${GPERF_OUTPUT}
            ${GPERF_FILE}
        DEPENDS 
            ${GPERF_FILE}
        COMMENT 
            "Compiling perfect hash table: ${BASENAME}.gperf -> .c"
        VERBATIM
    )

    # On append ce fichier à la liste des sources
    list(APPEND SOURCES
        ${GPERF_OUTPUT}
    )
endforeach()


# ===============================================
# FINALLY : CREATE THE LIBRARY
# ===============================================
# Add the common function sources
list(APPEND SOURCES
    src/commands/scpi/custom/actions/scpi_actions_get_r.cpp
    src/commands/scpi/custom/actions/scpi_actions_reset.cpp
    src/commands/scpi/custom/actions/scpi_actions_set.cpp
    src/commands/scpi/custom/analog/scpi_analog_input_r.cpp
    src/commands/scpi/custom/analog/scpi_analog_output.cpp
    src/commands/scpi/custom/analog/scpi_analog_temp_r.cpp
    src/commands/scpi/custom/configuration/scpi_conf_load.cpp
    src/commands/scpi/custom/configuration/scpi_conf_volt.cpp
    src/commands/scpi/custom/configuration/scpi_conf_volt_r.cpp
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
    src/commands/scpi/custom/logger/scpi_log_list.cpp
    src/commands/scpi/custom/prog/scpi_prog_connect.cpp
    src/commands/scpi/custom/prog/scpi_prog_detect.cpp
    src/commands/scpi/custom/prog/scpi_prog_device.cpp
    src/commands/scpi/custom/prog/scpi_prog_dump.cpp
    src/commands/scpi/custom/prog/scpi_prog_flash.cpp
    src/commands/scpi/custom/prog/scpi_prog_read.cpp
    src/commands/scpi/custom/prog/scpi_prog_status.cpp
    src/commands/scpi/custom/prog/scpi_prog_verify.cpp
    src/commands/scpi/custom/sequence/scpi_seq_add.cpp
    src/commands/scpi/custom/sequence/scpi_seq_get.cpp
    src/commands/scpi/custom/sequence/scpi_seq_new.cpp
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
    src/commands/shell/custom/shell_actions.cpp
    src/commands/shell/custom/shell_analog.cpp
    src/commands/shell/custom/shell_conf.cpp
    src/commands/shell/custom/shell_io.cpp
    src/commands/shell/custom/shell_log.cpp
    src/commands/shell/custom/shell_prog.cpp
    src/commands/shell/custom/shell_seq.cpp
    src/commands/shell/custom/shell_spy.cpp
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