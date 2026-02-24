# EtherBench Terminal & Binary Protocol Specification

This document defines the unified command interface for both human-readable text terminals (Serial VCOM / Telnet / SSH) and the binary protocol used by desktop applications.

## 1. The Binary Frame Protocol
To allow desktop apps to parse data efficiently without string manipulation, binary commands are wrapped in a strict frame structure.

**Frame Structure:** `[SYNC1] [SYNC2] [LEN] [OPCODE] [PAYLOAD...] [CRC16]`
* **SYNC1:** `0xEB` (EtherBench)
* **SYNC2:** `0x90` 
* **LEN:** 1 Byte (Length of Payload only)
* **OPCODE:** 1 Byte (The specific command ID)
* **PAYLOAD:** 0 to 255 Bytes
* **CRC16:** 2 Bytes (CCITT standard, covering LEN, OPCODE, and PAYLOAD)

---

## 2. Command Dictionary

### 2.1 Global Commands (0x0X)
**`status`**
* **Description:** Returns system health, uptime, connected targets, and current IO voltage (to be updated)
* **Text Syntax:** `status`
* **Binary Opcode:** `0x01`
* **Binary Payload:** None (`0x00`)

**`reset`**
* **Description:** Triggers a soft system reset of the EtherBench.
* **Text Syntax:** `reset`
* **Binary Opcode:** `0x0F`
* **Binary Payload:** None (`0x00`)

### 2.2 Hardware Features (0x1X)
*(Note: JTAG/SWD is handled autonomously via the dedicated CMSIS-DAP USB interface and is excluded from manual terminal control).*

**`hw-send`**
* **Description:** Transmits data over the specified bus.
* **Text Syntax:** `hw-send <uart|spi|i2c|can> <hex_data>`
* **Binary Opcode:** `0x10`
* **Binary Payload:** `[Bus ID (1 byte)] [Data (N bytes)]`

**`hw-read`**
* **Description:** Reads a specified number of bytes from the bus.
* **Text Syntax:** `hw-read <uart|spi|i2c|can> <address (I2C / SPI)> <num_bytes>`
* **Binary Opcode:** `0x11`
* **Binary Payload:** `[Bus ID (1 byte)] [address (2 bytes)] [Length (1 byte)]`

**`set-voltage`**
* **Description:** Configures the reference IO voltage for the target board/level shifters.
* **Text Syntax:** `set-voltage <volts>` (e.g., `set-voltage 1.8`)
* **Binary Opcode:** `0x12`
* **Binary Payload:** `[Voltage * 10 (1 byte)]` (e.g., `0x12` for 1.8V)

**`read-current`**
* **Description:** Reads the onboard INA226/INA219 to report target power draw.
* **Text Syntax:** `read-current`
* **Binary Opcode:** `0x13`
* **Binary Payload:** None. (Returns: `[Current_mA (uint16_t)]`)

**`analog-out` / `analog-in`**
* **Description:** Sets a DAC output voltage or reads an ADC input pin.
* **Text Syntax:** `analog-out <volts>` / `analog-in <channel 1|2>`
* **Binary Opcode:** `0x14` (Out) / `0x15` (In)

**`set-clock`**
* **Description:** Outputs a continuous clock signal on the dedicated CLK_OUT pin.
* **Text Syntax:** `set-clock <freq_hz>`
* **Binary Opcode:** `0x16`
* **Binary Payload:** `[Frequency_Hz (uint32_t)]`

### 2.3 Logs and IO Feeds (0x2X)
*Live feeds are ephemeral (cleared when the terminal session disconnects). Logs are persistent across reboots.*

**`feed-sub`**
* **Description:** Subscribes the current terminal (VCOM/SSH) to a live data stream.
* **Text Syntax:** `feed-sub <uart|can|system>`
* **Binary Opcode:** `0x20`
* **Binary Payload:** `[Stream ID (1 byte)]`

**`feed-unsub`**
* **Description:** Stops streaming the specified feed to the current session.
* **Text Syntax:** `feed-unsub <uart|can|system>`
* **Binary Opcode:** `0x21`
* **Binary Payload:** `[Stream ID (1 byte)]`

**`log-set`**
* **Description:** Routes a data stream to a persistent file on the storage drive.
* **Text Syntax:** `log-set <uart|can> <filename>`
* **Binary Opcode:** `0x22`
* **Binary Payload:** `[Stream ID (1 byte)] [Null-term String]`

**`log-clear`**
* **Description:** Stops writing the specified stream to disk.
* **Text Syntax:** `log-clear <uart|can>`
* **Binary Opcode:** `0x23`
* **Binary Payload:** `[Stream ID (1 byte)]`

### 2.4 Programming & Debugging (0x3X)
**`target-detect`**
* **Description:** Pings the SWD/JTAG lines to read the target MCU's IDCODE.
* **Text Syntax:** `target-detect`
* **Binary Opcode:** `0x30`

**`target-program`**
* **Description:** Flashes a binary file from the internal storage to the connected target.
* **Text Syntax:** `target-program <path_to_bin>` (e.g., `target-program /sd/fw.bin`)
* **Binary Opcode:** `0x31`
* **Binary Payload:** `[Null-term Path String]`

### 2.5 File System (0x4X)
*Mounted volumes are `/sd` (SD Card) and `/flash` (QSPI). Note: Text editing is omitted; use USB Mass Storage to edit files directly on a host PC.*

**`pwd`**
* **Description:** Prints the current working directory.
* **Text Syntax:** `pwd`
* **Binary Opcode:** `0x40`

**`ls`**
* **Description:** Lists files and directories in the current or specified path.
* **Text Syntax:** `ls [path]`
* **Binary Opcode:** `0x41`
* **Binary Payload:** `[Null-term Path String]`

**`mkdir`**
* **Description:** Creates a new directory.
* **Text Syntax:** `mkdir <path>`
* **Binary Opcode:** `0x42`

**`cp`**
* **Description:** Copies a file (useful for moving logs from `/flash` to `/sd`).
* **Text Syntax:** `cp <source> <dest>`
* **Binary Opcode:** `0x43`

**`cat`**
* **Description:** Dumps the contents of a text file to the terminal.
* **Text Syntax:** `cat <file>`
* **Binary Opcode:** `0x44`

**`cd`**
* **Description:** Move the actual place into another
* **Text Syntax:** `cd <dir>`
* **Binary Opcode:** `0x45`

### 2.6 Spy system (0x5X)
* Enable to spy a bus, in a passive way, just to see what happen, and when. Can be logged*

**`spy`**
* **Description:** Set the peripheral as a slave, and record every data on it.
* **Text Syntax:** `spy <uart|spi|i2c|can>`
* **Binary Opcode:** `0x10`
* **Binary Payload:** `[Bus ID (1 byte)] [Data (N bytes)]`

---

## 3. C++ API Architecture (The Command Parser)

The terminal logic uses a C++ struct array to link text commands, binary opcodes, and execution callbacks together in a zero-allocation, RTOS-friendly way.

```cpp
#include <stdint.h>
#include <string.h>

// 1. Define the callback signature
typedef bool (*CommandCallback)(const uint8_t* payload, uint8_t len, const char* arg_string);

// 2. Define the Command Dictionary Struct
struct EtherBenchCommand {
    const char* text_command;
    uint8_t binary_opcode;
    const char* help_text;
    CommandCallback execute;
};

// 3. Implement the callbacks
bool Cmd_HwSend(const uint8_t* payload, uint8_t len, const char* arg_string) {
    // If binary payload exists, use it. Otherwise, parse the arg_string!
    // e.g., hw-send spi 0xFF
    return true;
}

// 4. Build the Static Dictionary
static const EtherBenchCommand command_table[] = {
    {"status",       0x01, "Shows system health and voltages", Cmd_Status},
    {"hw-send",      0x10, "Usage: hw-send <bus> <data>",      Cmd_HwSend},
    {"set-voltage",  0x12, "Usage: set-voltage <volts>",       Cmd_SetVoltage},
    {"feed-sub",     0x20, "Usage: feed-sub <stream>",         Cmd_FeedSub},
    {"ls",           0x41, "Lists directory contents",         Cmd_Ls}
};
#define NUM_COMMANDS (sizeof(command_table) / sizeof(command_table[0]))
