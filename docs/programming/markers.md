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

| Offset | Size (B) | Description                                      |
| :----: | :------: | :----------------------------------------------- |
| 0x00   | 2        | Page 0 marker, constant to 0xEBB0                |
| 0x02   | 2        | Page version, must be 0x1000                     |
| 0x04   | 4        | Hardware version. Interpreted as M.m.pp values.  |
| 0x08   | 2        | Default asked voltage. Interpreted as XX mV.     |
| 0x0A   | 2        | Maximal current requested. Interpreted as XX mA. |
| 0x0C   | 2        | Lowest possible voltage. Interpreted as XX mV.   |
| 0x0E   | 2        | Highest possible voltage. Interpreted as XX mV.  |
| 0x10   | 2        | Custom flags. See bottom definition.             |
| 0x12   | 2        | Clock frequency. Interpreted as XX MHz.          |
| 0x14   | 4        | Optionnal page 0                                 |
| 0x18   | 4        | Optionnal page 1                                 |
| 0x1C   | 4        | Config CRC                                       |

### Flags

Flags are individual bits, that identify a specific option

| Bit | Name                     | Description                                                                                     |
| :-: | :----------------------- | :---------------------------------------------------------------------------------------------- |
| 0   | Isolated board           | Indicate that the board isolate it's ground relatively to the master ground.                    |
| 1   | Require clock            | Indicate that the board require a clock to operate.                                             |
| 2   | Required USB             | Indicate that the board use the onboard USB over the PCIe slot.                                 |
| 3   | Active board             | Indicate that the board include active components on between the host and the IOs.              |
| 4   | Reserved                 | /                                                                                               |
| 5   | Reserved                 | /                                                                                               |
| 6   | Non standard form factor | Indicate that the board as a non standard form factor.                                          |
| 7   | Ignore mouting check     | Indicate to ignore the mouting security bits. This feature must be also forced from the shell.  |

### Optionnal pages

Optionnal pages can be passed to the structure, to extend the functions of the latter one. The structure is quite simple:
All of these are designed to fit over a single four byte space.

| Offset | Size  | Description         |
| :----: | :---: | :------------------ |
| 0x00   | 2     | Address of the page | 
| 0x02   | 2     | Page type (0xEBXX)  |

If unused, let 0xFFFFFFFF as the page ID. 

## Optionnal pages

As optionnal pages, a lot can be passed to expand the abilities.
Here the different structures that can be passed:

| Name              |  Type  | Description                                                                                                               |
| :---------------: | :----: | :------------------------------------------------------------------------------------------------------------------------ |
| Pages             | 0xEBB1 | Store up to 8 optionnal pages pointers. A single entity of this is possible.                                              |
| Peripheral config | 0xEBB2 | Store peripheral basic configuration, to ensure a direct operation. Usefull with specific active components on the board. |
| Board name        | 0xEBB3 | Store the human name of the board                                                                                         |
| Calibration       | 0xEBB4 | Store calibration values for the analog IOs                                                                               |

### Pages 

| Offset | Size (B) | Description                                      |
| :----: | :------: | :----------------------------------------------- |
| 0x00   | 2        | Pages marker, constant to 0xEBB1                 |
| 0x02   | 2        | Page CRC                                         |
| 0x04   | 4        | Optionnal page 0                                 |
| 0x08   | 4        | Optionnal page 1                                 |
| 0x0C   | 4        | Optionnal page 2                                 |
| 0x10   | 4        | Optionnal page 3                                 |
| 0x14   | 4        | Optionnal page 4                                 |
| 0x18   | 4        | Optionnal page 5                                 |
| 0x1C   | 4        | Optionnal page 6                                 |

Up to 7 pages can be added, maxing out at 8 optionnal pages in total.


### Peripherals 

| Offset | Size (B) | Description                                      |
| :----: | :------: | :----------------------------------------------- |
| 0x00   | 2        | Peripheral config marker, constant to 0xEBB2     |
| 0x02   | 2        | Page CRC                                         |
| 0x04   | 2        | Enabled peripherals (see mask at the bottom)     |
| 0x06   | 1        | GPIO Direction (4 LSB) : 1 : in; 0 : out         |
| 0x07   | 1        | GPIO Value (4 LSB)                               |
| 0x08   | 3        | UART 0 Config                                    |
| 0x0B   | 3        | UART 1 Config                                    |
| 0x0E   | 3        | UART 2 Config                                    |
| 0x11   | 3        | SPI Config                                       |
| 0x15   | 4        | CAN Config                                       |
| 0x19   | 4        | JTAG / SWD Config                                |
| 0x1D   | 3        | I2C Config                                       |

#### Peripherals flags

| Bit | Name                     |
| :-: | :----------------------- |
| 0   | UART 0                   |
| 1   | UART 1                   |
| 2   | UART 2                   |
| 3   | Reserved                 |
| 4   | I3C / I2C                |
| 5   | SPI                      |
| 6   | CAN                      |
| 7   | JTAG                     |
| 8   | Reserved                 |
| 9   | GPIO 0                   |
| 10  | GPIO 1                   |
| 11  | GPIO 2                   |
| 12  | GPIO 3                   |
| 13  | Reserved                 |
| 14  | Reserved                 |
| 15  | Reserved                 |

#### UART Config

| Offset | Size  | Description                                                                                                |
| :----: | :---: | :--------------------------------------------------------------------------------------------------------- |
| 0x00   | 2     | Speed : Baudrate / 100                                                                                     | 
| 0x02   | 1     | Bits 0-1 : Transfer size : 7 + 2'bXX. Bits 3-4 : Stop bits number : 2'bXX (1 or 2). Bit 7 : Enable parity. |

#### I2C Config

| Offset | Size  | Description                                                                                                |
| :----: | :---: | :--------------------------------------------------------------------------------------------------------- |
| 0x00   | 1     | Speed : Baudrate / 1000                                                                                    | 
| 0x01   | 1     | Bit 0 : Enable slave mode. Bit 2 : Enable 10 bit address. Bits 7-5 : Slave address [10-8]                  |
| 0x02   | 1     | Slave address [7:0]                                                                                        |

#### SPI Config

| Offset | Size  | Description                                                                                                |
| :----: | :---: | :--------------------------------------------------------------------------------------------------------- |
| 0x00   | 2     | Speed : Baudrate / 1000                                                                                    | 
| 0x02   | 1     | Transfer size (4-32)                                                                                       |

#### CAN Config

| Offset | Size  | Description                                                                                                |
| :----: | :---: | :--------------------------------------------------------------------------------------------------------- |
| 0x00   | 1     | ???                                                                                                        | 
| 0x01   | 1     | ???                                                                                                        |
| 0x00   | 2     | ???                                                                                                        | 
| 0x01   | 3     | ???                                                                                                        |

#### JTAG / SWD Config

| Offset | Size  | Description                                                                                                |
| :----: | :---: | :--------------------------------------------------------------------------------------------------------- |
| 0x00   | 2     | Speed : Baudrate / 1000                                                                                    | 
| 0x02   | 2     | Bit 0 : Connect under reset                                                                                |

### Board name

| Offset | Size (B) | Description                                      |
| :----: | :------: | :----------------------------------------------- |
| 0x00   | 2        | Pages marker, constant to 0xEBB3                 |
| 0x02   | 2        | Page CRC                                         |
| 0x04   | 28       | ASCII coded name.                                |

### Calibration values

| Offset | Size (B) | Description                                      |
| :----: | :------: | :----------------------------------------------- |
| 0x00   | 2        | Pages marker, constant to 0xEBB4                 |
| 0x02   | 2        | Page CRC                                         |
| 0x04   | 4        | ADC 0 Offset (float)                             |
| 0x08   | 4        | ADC 1 Offset (float)                             |
| 0x0C   | 4        | ADC Gain (float)                                 |
| 0x10   | 4        | DAC 0 Offset (float)                             |
| 0x14   | 4        | DAC 1 Offset (float)                             |
| 0x18   | 4        | DAC Gain (float)                                 |
| 0x1C   | 2        | Calibration year                                 |
| 0x1E   | 1        | Calibration month                                |
| 0x1F   | 1        | Calibration day                                  |


