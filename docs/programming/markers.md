# Markers

All along the project, different structures are used.
One of the most important is the marker stored on the daughter-board, to identify the target we're working with.

This data must be stored on an I2C EEPROM at address 0x50 on the board. The page size used is 32 bytes, to match with any reference on the market.
Our is ST M24C64-RMN6TP from ST, but any reference that match theses options are good.
This chip is always powered with 3.3V, even when the main supply is OFF.

## Principle

The markers are based over a minimal set of information, stored within 32 bytes of data, and some optionnal pages that may store more data.
Thus, the protocol is extensible.

Optionnal pages are referenced within the first page.

## Page 0

This main page store the basic element, that ALL extensions board must have.
The data stored within is arranged as:

| **Offset** | **Size (Bytes)** | **Description**                                  |
| :--------: | :--------------: | :----------------------------------------------- |
|   `0x00`   |      **2**       | Page 0 marker, constant to 0xEBB0                |
|   `0x02`   |      **2**       | Page version, must be 0x1000                     |
|   `0x04`   |      **4**       | Hardware version. Interpreted as M.m.pp values.  |
|   `0x08`   |      **2**       | Default asked voltage. Interpreted as XX mV.     |
|   `0x0A`   |      **2**       | Maximal current requested. Interpreted as XX mA. |
|   `0x0C`   |      **2**       | Lowest possible voltage. Interpreted as XX mV.   |
|   `0x0E`   |      **2**       | Highest possible voltage. Interpreted as XX mV.  |
|   `0x10`   |      **2**       | Custom flags. See bottom definition.             |
|   `0x12`   |      **2**       | Clock frequency. Interpreted as XX MHz.          |
|   `0x14`   |      **4**       | Optionnal page 0                                 |
|   `0x18`   |      **4**       | Optionnal page 1                                 |
|   `0x1C`   |      **4**       | Config CRC                                       |

### Flags

Flags are individual bits, that identify a specific option

| **Bit** | **Name**                 | **Description**                                                                                |
| :-----: | :----------------------- | :--------------------------------------------------------------------------------------------- |
|   `0`   | Isolated board           | Indicate that the board isolate it's ground relatively to the master ground.                   |
|   `1`   | Require clock            | Indicate that the board require a clock to operate.                                            |
|   `2`   | Required USB             | Indicate that the board use the onboard USB over the PCIe slot.                                |
|   `3`   | Active board             | Indicate that the board include active components on between the host and the IOs.             |
|   `4`   | Reserved                 | /                                                                                              |
|   `5`   | Reserved                 | /                                                                                              |
|   `6`   | Non standard form factor | Indicate that the board as a non standard form factor.                                         |
|   `7`   | Ignore mouting check     | Indicate to ignore the mouting security bits. This feature must be also forced from the shell. |

### Optionnal pages

Optionnal pages can be passed to the structure, to extend the functions of the latter one. The structure is quite simple:
All of these are designed to fit over a single four byte space.

| **Offset** | **Size** | **Description**     |
| :--------: | :------: | :------------------ |
|   `0x00`   |  **2**   | Address of the page |
|   `0x02`   |  **2**   | Page type (0xEBXX)  |

If unused, let 0xFFFFFFFF as the page ID.

## Optionnal pages

As optionnal pages, a lot can be passed to expand the abilities.
Here the different structures that can be passed:

|                        **Name**                         | **Type** | **Description**                                                                                                           |
| :-----------------------------------------------------: | :------: | :------------------------------------------------------------------------------------------------------------------------ |
|          [**Pages**](markers/markers_pages.md)          | `0xEBB1` | Store up to 8 optionnal pages pointers. A single entity of this is possible.                                              |
| [**Peripheral config**](markers/markers_peripherals.md) | `0xEBB2` | Store peripheral basic configuration, to ensure a direct operation. Usefull with specific active components on the board. |
|        [**Board name**](markers/markers_name.md)        | `0xEBB3` | Store the human name of the board                                                                                         |
|    [**Calibration**](markers/markers_calibration.md)    | `0xEBB4` | Store calibration values for the analog IOs                                                                               |
|  [**Serial Number**](markers/markers_serial_number.md)  | `0xEBB5` | Store informations about how the board itself, to identify it.                                                            |
