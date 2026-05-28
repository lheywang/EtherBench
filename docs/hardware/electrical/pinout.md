# Pinout & Hardware Mapping

The core of the EtherBench motherboard features an STM32H5 in a VFBGA201 package, exposing an extensive array of hardware
peripherals. To streamline firmware development (BSP handle definition) and facilitate non-intrusive laboratory troubleshooting,
all active pins are detailed below.

Testpoints (TP) are specified only for signals where trace velocity, parasitic capacitance, and hardware layout constraints allow
safe physical probing.

## Host communication

These signals are used as the core functions, such as host communication or flash storage.

|      Instance      |                                         Signal                                          |                                       Pin                                        |                                   BGA                                   | Description                                                 |
| :----------------: | :-------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------- |
|      `USBHS1`      |                                      `DP`<br>`DM`                                       |                                `PA12` <br> `PA11`                                |                            `B15` <br> `C15`                             | USB peripheral, routed to the hub as a device.              |
|     `USB_SUSP`     |                                       `USB_SUSP`                                        |                                      `PD2`                                       |                                  `D12`                                  | USB Upstream suspended signal.                              |
|      `USB_HS`      |                                        `USB_HS`                                         |                                      `PD3`                                       |                                  `D11`                                  | USB Upstream as high-speed signal.                          |
|    `USB_RESET`     |                                       `USB_RESET`                                       |                                      `PH13`                                      |                                  `E12`                                  | USB hub reset signal                                        |
|      `UCPD1`       |                         `CC1`<br>`CC2`<br>`DB_CC1`<br>`DB_CC2`                          |                        `PB13`<br>`PB14`<br>`PA9`<br>`PC9`                        |                    `P13`<br>`R14`<br>`E15`<br>`F14`                     | USB-C signals. Routed directly to the USB-C port.           |
|       `ETH`        | `CLK`<br>`MDC`<br>`MDIO`<br>`CRS_DV`<br>`TX_EN`<br>`RXD0`<br>`RXD1`<br>`TXD0`<br>`TXD1` | `PA1`<br>`PC1`<br>`PA2`<br>`PA7`<br>`PB11`<br>`PC4`<br>`PC5`<br>`PB12`<br>`PB15` | `N2`<br>`M3`<br>`P2`<br>`R3`<br>`R13`<br>`N5`<br>`P5`<br>`P12`<br>`R15` | Ethernet signals, routed to the PHY.                        |
|    `ETH_RESET`     |                                       `ETH_RESET`                                       |                                      `PD9`                                       |                                  `P14`                                  | Ethernet PHY reset                                          |
|     `OCTOSPI1`     |                   `CLK`<br>`IO0`<br>`IO1`<br>`IO2`<br>`IO3`<br>`NCS`                    |               `PF10`<br>`PF8`<br>`PF9`<br>`PF7`<br>`PF6`<br>`PE11`               |              `L1`<br>`L3`<br>`L2`<br>`K1`<br>`K2`<br>`P10`              | QSPI Flash signals.                                         |
|`DEBUG`  |              `SWCLK`<br>`SWDIO`                                                                     |                                 `PA14`<br>`PA13`                                 |                             `A14`<br>`A15`                              | SWD signals, routed to a standard header for initial flash. |
|      `SDMMC2`      |                     `SCK`<br>`CMD`<br>`D0`<br>`D1`<br>`D2`<br>`D3`                      |              `PD6`<br>`PD7`<br>`PG9`<br>`PG10`<br>`PG11`<br>`PG12`               |            `B11`<br>`A11`<br>`C10`<br>`B10`<br>`B9`<br>`B8`             | SD systems. Limited to 3.3V bus.                            |
|     `EVENTOUT`     |                                       `TRIG_OUT`                                        |                                      `PD10`                                      |                                  `N15`                                  | Trigger output.                                             |
|       `EXTI`       |                                        `TRIG_IN`                                        |                                      `PD8`                                       |                                  `N15`                                  | Trigger input                                               |


## Programmer

These signals are the one used as the SWD/JTAG signals to flash the probe. They're placed appart, as they're runned not used as
standard peripherals.

|    Instance    |               Signal               |                   Pin                    |                  BGA                   | Description                |
| :------------: | :--------------------------------: | :--------------------------------------: | :------------------------------------: | :------------------------- |
| `SWD` / `JTAG` | `SCLK`<br>`MISO`<br>`MOSI`<br>`IO` | `PC10`-`PI1`<br>`PI2`<br>`PI3`<br>`PC12` | `D14`-`B14`<br>`C14`<br>`C13`<br>`A12` | DUT Programmation signals. |

### Operation principle

As the SWD bus require a bi-directionnal communication, we used an SPI peripheral that can do both, here, SPI3. The SPI2
peripheral is used for JTAG, where TDI and TDO pins are used. The second SPI slave run as a full-duplex slave to ensure
synchronisation of the two peripherals.

When running in SWD mode, the SPI3 peripheral can be reconfigured to a serial receiver to provide the SWO ability.

## DUT communication

These signals are used by the hardware IO to the DUT, on the standard serial interfaces.

|   Instance    |                              Signal                              |                         Pin                         |                     BGA                      | Description                                           |
| :-----------: | :--------------------------------------------------------------: | :-------------------------------------------------: | :------------------------------------------: | :---------------------------------------------------- |
|    `MCO1`     |                              `MCO1`                              |                        `PA8`                        |                    `F15`                     | Clock output for the DUT.                             |
|    `I3C1`     |                          `SCL`<br>`SDA`                          |                   `PB8`<br>`PB9`                    |                 `A5`<br>`B4`                 | I3C master / slave.                                   |
|   `USART10`   |                  `TX`<br>`RX`<br>`RTS`<br>`CTS`                  |         `PE3`<br>`PE2`<br>`PG14`<br>`PG13`          |         `A1`<br>`A2`<br>`A7`<br>`A8`         | Full featured USART bus.                              |
|   `USART5`    |                           `TX`<br>`RX`                           |                   `PB6`<br>`PB5`                    |                 `B6`<br>`A6`                 | Rx/Tx only featured USART bus.                        |
|   `USART11`   |                           `TX`<br>`RX`                           |                   `PF3`<br>`PF4`                    |                 `J2`<br>`J3`                 | Rx/Tx only featured USART bus.                        |
|    `SPI4`     |          `SCLK`<br>`MISO`<br>`MOSI`<br>`NSS0`<br>`NSS1`          |     `PE12`<br>`PE5`<br>`PE6`<br>`PI0`<br>`PC7`      |   `R10`<br>`B2`<br>`B3`<br>`E14`<br>`G15`    | Full duplex SPI Master. NSS are done by GPIOs.        |
|   `FDCAN1`    |                           `TX`<br>`RX`                           |                   `PE1`<br>`PE0`                    |                 `A3`<br>`A4`                 | FDCAN peripheral.                                     |
|    `ADC1`     |                          `IN2`<br>`IN5`                          |                   `PF11`<br>`PB1`                   |                 `R6`<br>`R4`                 | Analog input.                                         |
|    `DAC1`     |                         `OUT1`<br>`OUT2`                         |                   `PA4`<br>`PA5`                    |                 `N4`<br>`P4`                 | Analog output.                                        |
|    `GPIO`     | `OD_W_1`<br>`OD_W_2`<br>`OD_R_1`<br>`OD_R_2`<br>`PP_1`<br>`PP_2` | `PI8`<br>`PI9`<br>`PI11`<br>`PH2`<br>`PI5`<br>`PI4` | `D2`<br>`D3`<br>`D4`<br>`C4`<br>`E4`<br>`F4` | GPIO (2 pair of open drain OUT + READ + 2 push pull). |
|   `BUCK_EN`   |                               `EN`                               |                        `PI7`                        |                     `C2`                     | DUT buck enable                                       |
|  `BUCK_INT`   |                              `INT`                               |                        `PI6`                        |                     `C3`                     | DUT buck inerrupt                                     |
|  `DUT_RESET`  |                             `RESET`                              |                        `PH5`                        |                     `J4`                     | DUT reset signal                                      |
| `DUT_PRESENT` |                            `PRESENT`                             |                        `PH4`                        |                     `H4`                     | DUT present signal                                    |

## User IO

These signals are used by the hardware to show informations to the user.

|   Instance    |     Signal     |                         Pin                         |                      BGA                      | Description                   |
| :-----------: | :------------: | :-------------------------------------------------: | :-------------------------------------------: | :---------------------------- |
|    `TIM13`    |   `aRGB_OUT`   |                        `PA6`                        |                     `P3`                      | aRGB output for the led ring. |
| `TIM1`-`TIM2` |  `User leds`   | `PE9`-`PE13`-`PE14`-`PH9`-`PA3`-`PA15`-`PB3`-`PB10` | `P9`-`N11`-`P11`-`M13`-`R2`-`A13`-`A10`-`R12` | PWM Leds outputs.             |
| `GPIO_INPUT`  | `User buttons` |                  `PH6`-`PH7`-`PH8`                  |               `M11`-`M12`-`N12`               | User buttons                  |
| `GPIO_INPUT`  |  `User reset`  |                       `PD12`                        |                     `N13`                     | User reset request.           |

## Miscellaneous

These signals describe all the others pins, for a lot of different functions that may not be linked together.

|  Instance   |                                               Signal                                               |                                  Pin                                   |                               BGA                                | Description                               |
| :---------: | :------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------: | :--------------------------------------------------------------: | :---------------------------------------- |
|   `I2C2`    |                                           `SCL`<br>`SDA`                                           |                             `PF1`<br>`PF0`                             |                           `H3`<br>`E2`                           | I2C for management and internal usage.    |
|   `I2C4`    |                                     `SCL`<br>`SDA`<br>`ALERT`                                      |                       `PH11`<br>`PH12`<br>`PH10`                       |                     `L12`<br>`K12`<br>`L13`                      | SMBUS for the USB hub management.         |
|  `USART9`   |                                   `TX`<br>`RX`<br>`IN`<br>`OUT`                                    |                  `PD15`<br>`PD14`<br>`PD13`<br>`PG2`                   |                 `L14`<br>`M14`<br>`M15`<br>`L15`                 | Serial bus for the INTERCOM system.       |
|   `TIM3`    |                                               `PWM1`                                               |                                 `PC6`                                  |                              `H15`                               | PWM Output for the optionnal fan.         |
|  `RCC_8M`   |                                           `IN`<br>`OUT`                                            |                             `PH0`<br>`PH1`                             |                           `G1`<br>`H1`                           | Crystal for the 8 MHz clock source.       |
| `RCC_32kHz` |                                           `IN`<br>`OUT`                                            |                            `PC14`<br>`PC15`                            |                           `E1`<br>`F1`                           | Crystal for the 32.768 kHz Clock source.  |
|   `DEBUG`   | `DBG_01`<br>`DBG_02`<br>`DBG_03`<br>`DBG_04`<br>`DBG_IN1`<br>`DBG_IN2`<br>`DBG_LED1`<br>`DBG_LED2` | `PG1`<br>`PG0`<br>`PF15`<br>`PF14`<br>`PG7`<br>`PG6`<br>`PG4`<br>`PG3` | `N7`<br>`M7`<br>`P7`<br>`R7`<br>`J14`<br>`J15`<br>`K14`<br>`K15` | Custom debug pins for the firmware build. |
|  `PRESENT`  |                                          `BOARD_PRESENT`                                           |                                 `PC13`                                 |                               `D1`                               | Daughter board presence detection.        |
|  `SCREWED`  |                                             `SCREWED`                                              |                                 `PE4`                                  |                               `B1`                               | Daughter board screwed detection.         |
|    `OE`     |                                                `OE`                                                |                                 `PF2`                                  |                               `H2`                               | Buffer output enable.                     |
| `POWER_OK`  |                                              `PGOOD`                                               |                                 `PE7`                                  |                               `R8`                               | Master regulator power good signal.       |


