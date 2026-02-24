# EtherBench Terminal & Binary Protocol Specification

This document defines the unified command interface for both human-readable text terminals (Serial VCOM/SSH) and the binary protocol used by desktop applications.

## 1. The Binary Frame Protocol
To allow desktop apps to parse data efficiently without string manipulation, binary commands are wrapped in a strict frame structure.

**Frame Structure:** `[SYNC1] [SYNC2] [LEN] [OPCODE] [PAYLOAD...] [CRC16]`
* **SYNC1:** `0xEB` (EtherBench)
* **SYNC2:** `0x90` 
* **LEN:** 1 Byte (Length of Payload only)
* **OPCODE:** 1 Byte (The specific command ID)
* **PAYLOAD:** 0 to 255 Bytes
* **CRC16:** 2 Bytes (CCITT standard, covering LEN, OPCODE, and PAYLOAD)

## 2. Command Dictionary

### 2.1 System Information
**`status`**
* **Description:** Returns the current RTOS thread states, memory usage, and uptime.
* **Text Syntax:** `status`
* **Binary Opcode:** `0x01`
* **Binary Payload:** None (`0x00`)

**`net-info`**
* **Description:** Prints current IP, Subnet, Gateway, MAC, and DHCP status.
* **Text Syntax:** `net-info`
* **Binary Opcode:** `0x02`
* **Binary Payload:** None (`0x00`)

### 2.2 Target Power Control
**`set-voltage`**
* **Description:** Configures the DAC/Level shifters for the target JTAG reference voltage.
* **Text Syntax:** `set-voltage <target> <volts>` (e.g., `set-voltage jtag 1.8`)
* **Binary Opcode:** `0x10`
* **Binary Payload:** `[Target ID (1 byte)] [Voltage * 10 (1 byte)]` (e.g., `0x01 0x12` for 1.8V)

**`read-current`**
* **Description:** Reads the INA226/INA219 sensor to show target current draw in mA.
* **Text Syntax:** `read-current`
* **Binary Opcode:** `0x11`
* **Binary Payload:** None (`0x00`)
* **Binary Response Payload:** `[Current_mA (uint16_t)]`

### 2.3 Storage & Logging
**`sd-format`**
* **Description:** Erases and formats the SD card to FAT32. Requires confirmation.
* **Text Syntax:** `sd-format --force`
* **Binary Opcode:** `0x20`
* **Binary Payload:** `[Force Flag (1 byte)]` (`0x01` for yes)

**`log-start`**
* **Description:** Begins recording UART/Current data to the QSPI/SD.
* **Text Syntax:** `log-start <filename>`
* **Binary Opcode:** `0x21`
* **Binary Payload:** `[Null-terminated string (N bytes)]`

### 2.4 Configuration
**`mode`**
* **Description:** Switches the primary USB function (requires software reboot).
* **Text Syntax:** `mode <usb|dap>`
* **Binary Opcode:** `0x30`
* **Binary Payload:** `[Mode ID (1 byte)]` (`0x00` = USB, `0x01` = DAP)
