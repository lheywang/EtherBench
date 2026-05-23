# Peripherals

| **Offset** | **Size (Bytes)** | **Description**                              |
| :--------: | :--------------: | :------------------------------------------- |
|   `0x00`   |      **2**       | Peripheral config marker, constant to 0xEBB2 |
|   `0x02`   |      **2**       | Page CRC                                     |
|   `0x04`   |      **2**       | Enabled peripherals (see mask at the bottom) |
|   `0x06`   |      **1**       | GPIO Direction (4 LSB) : 1 : in; 0 : out     |
|   `0x07`   |      **1**       | GPIO Value (4 LSB)                           |
|   `0x08`   |      **3**       | UART 0 Config                                |
|   `0x0B`   |      **3**       | UART 1 Config                                |
|   `0x0E`   |      **3**       | UART 2 Config                                |
|   `0x11`   |      **3**       | SPI Config                                   |
|   `0x15`   |      **4**       | CAN Config                                   |
|   `0x19`   |      **4**       | JTAG / SWD Config                            |
|   `0x1D`   |      **3**       | I2C Config                                   |

## Peripherals flags

| **Bit** | **Name**                 |
| :-----: | :----------------------- |
|   `0`   | UART 0                   |
|   `1`   | UART 1                   |
|   `2`   | UART 2                   |
|   `3`   | Reserved (constant to 0) |
|   `4`   | I3C / I2C                |
|   `5`   | SPI                      |
|   `6`   | CAN                      |
|   `7`   | JTAG                     |
|   `8`   | Reserved (constant to 0) |
|   `9`   | GPIO 0                   |
|  `10`   | GPIO 1                   |
|  `11`   | GPIO 2                   |
|  `12`   | GPIO 3                   |
|  `13`   | Reserved (constant to 0) |
|  `14`   | Reserved (constant to 0) |
|  `15`   | Reserved (constant to 0) |

## UART Config

| **Offset** | **Size** | **Description**                                                                                            |
| :--------: | :------: | :--------------------------------------------------------------------------------------------------------- |
|   `0x00`   |  **2**   | Speed : Baudrate / 100                                                                                     |
|   `0x02`   |  **1**   | Bits 0-1 : Transfer size : 7 + 2'bXX. Bits 3-4 : Stop bits number : 2'bXX (1 or 2). Bit 7 : Enable parity. |

## I2C Config

| **Offset** | **Size** | **Description**                                                                           |
| :--------: | :------: | :---------------------------------------------------------------------------------------- |
|   `0x00`   |  **1**   | Speed : Baudrate / 1000                                                                   |
|   `0x01`   |  **1**   | Bit 0 : Enable slave mode. Bit 2 : Enable 10 bit address. Bits 7-5 : Slave address [10-8] |
|   `0x02`   |  **1**   | Slave address [7:0]                                                                       |

## SPI Config

| **Offset** | **Size** | **Description**         |
| :--------: | :------: | :---------------------- |
|   `0x00`   |  **2**   | Speed : Baudrate / 1000 |
|   `0x02`   |  **1**   | Transfer size (4-32)    |

## CAN Config

| **Offset** | **Size** | **Description** |
| :--------: | :------: | :-------------- |
|   `0x00`   |  **1**   | ???             |
|   `0x01`   |  **1**   | ???             |
|   `0x00`   |  **2**   | ???             |
|   `0x01`   |  **3**   | ???             |

## JTAG / SWD Config

| **Offset** | **Size** | **Description**             |
| :--------: | :------: | :-------------------------- |
|   `0x00`   |  **2**   | Speed : Baudrate / 1000     |
|   `0x02`   |  **2**   | Bit 0 : Connect under reset |

## Yaml arguments

When using the automated page builder, available on the EtherBenchProbe repo, each bus is configured by it's own key. Therefore, are searched:

- uart0
- uart1
- uart2
- spi
- can
- jtag or swd
- i2C

The present of any key will trigger the build of the page. Missing keys are going to be filled with the default value.
For each of them, the following key are searched.

### UART

|  **Key**  | **Format** | **Default value** |
| :-------: | ---------- | ----------------- |
| baudrate  | Integer    | 115200            |
|   size    | Integer    | 8                 |
| stop bits | Integer    | 1                 |
|  partity  | Integer    | 0                 |

### I2C

|    **Key**    | **Format** | **Default value** |
| :-----------: | ---------- | ----------------- |
|   baudrate    | Integer    | 115200            |
| slave address | Integer    | 0                 |
|   slave mod   | Integer    | 0                 |

### SPI

| **Key**  | **Format**                 | **Default value** |
| :------: | -------------------------- | ----------------- |
| baudrate | Any SI value (1MHz, 16MHz) | "1MHz"            |
|   size   | Integer                    | 8                 |

### CAN

| **Key**  | **Format**                 | **Default value** |
| :------: | -------------------------- | ----------------- |
| baudrate | Any SI value (1MHz, 16MHz) | "1MHz"            |
|   size   | Integer                    | 8                 |

### JTAG/SWD

| **Key**  | **Format**                 | **Default value** |
| :------: | -------------------------- | ----------------- |
| baudrate | Any SI value (1MHz, 16MHz) | "1MHz"            |
|   size   | Integer                    | 8                 |
