# Pinout & Hardware Mapping

The core of the EtherBench motherboard features an STM32H5 in a VFBGA201 package, exposing an extensive array of hardware
peripherals. To streamline firmware development (BSP handle definition) and facilitate non-intrusive laboratory troubleshooting,
all active pins are detailed below.

Testpoints (TP) are specified only for signals where trace velocity, parasitic capacitance, and hardware layout constraints allow
safe physical probing.

## Host communication

These signals are used as the core functions, such as host communication or flash storage.

| Peripheral |  Instance  |                                         Signal                                          |                                       Pin                                        |                                   BGA                                   |                        Testpoint                         |                        Description                         |
| :--------: | :--------: | :-------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------: | :---------------------------------------------------------------------: | :------------------------------------------------------: | :--------------------------------------------------------: |
|    USB     |  `USBHS1`  |                                      `DP`<br>`DM`                                       |                                `PA12` <br> `PA11`                                |                            `B15` <br> `C15`                             |                           `/`                            |       USB peripheral, routed to the hub as a device        |
|  Ethernet  |   `ETH`    | `CLK`<br>`MDC`<br>`MDIO`<br>`CRS_DV`<br>`TX_EN`<br>`RXD0`<br>`RXD1`<br>`TXD0`<br>`TXD1` | `PA1`<br>`PC1`<br>`PA2`<br>`PA7`<br>`PB11`<br>`PC4`<br>`PC5`<br>`PB12`<br>`PB15` | `N2`<br>`M3`<br>`P2`<br>`R3`<br>`R13`<br>`N5`<br>`P5`<br>`P12`<br>`R15` |                           `/`                            |            Ethernet signals, routed to the PHY.            |
|  OCTOSPI   | `OCTOSPI1` |                   `CLK`<br>`IO0`<br>`IO1`<br>`IO2`<br>`IO3`<br>`NCS`                    |               `PF10`<br>`PF8`<br>`PF9`<br>`PF7`<br>`PF6`<br>`PE11`               |              `L1`<br>`L3`<br>`L2`<br>`K1`<br>`K2`<br>`P10`              | `TPxx`<br>`TPxx`<br>`TPxx`<br>`TPxx`<br>`TPxx`<br>`TPxx` |                   Internal flash signals                   |
|  Host-SWD  |            |                                   `SWCLK`<br>`SWDIO`                                    |                                 `PA14`<br>`PA13`                                 |                             `A14`<br>`A15`                              |                            /                             | SWD signals, routed to a standard header for initial flash |
|    UCPD    |  `UCPD1`   |                         `CC1`<br>`CC2`<br>`DB_CC1`<br>`DB_CC2`                          |                            `PB13`<br>`PB14`<br>`<br>`                            |                       `PB13`<br>`PB14`<br>`<br>`                        |                 `P13`<br>`R14`<br>`<br>`                 |  USB-C signals. Routed directly to the USB-C device port.  |
|   SDMMC    |  `SDMMC2`  |                     `SCK`<br>`CMD`<br>`D0`<br>`D1`<br>`D2`<br>`D3`                      |              `PD6`<br>`PD7`<br>`PG9`<br>`PG10`<br>`PG11`<br>`PG12`               |            `B11`<br>`A11`<br>`C10`<br>`B10`<br>`B9`<br>`B8`             |                            /                             |              SD systems. Limited to 3.3V bus.              |

## Programmer

These signals are the one used as the SWD/JTAG signals to flash the probe. They're placed appart, as they're runned not used as
standard peripherals.

| Peripheral |     Instance     |               Signal               |                   Pin                    |                  BGA                   | Testpoint |        Description        |
| :--------: | :--------------: | :--------------------------------: | :--------------------------------------: | :------------------------------------: | :-------: | :-----------------------: |
| SWD / JTAG | `SPI3`<br>`SPI2` | `SCLK`<br>`MISO`<br>`MOSI`<br>`IO` | `PC10`-`PI1`<br>`PI2`<br>`PI3`<br>`PC12` | `D14`-`B14`<br>`C14`<br>`C13`<br>`A12` |           | DUT Programmation signals |

### Operation principle

As the SWD bus require a bi-directionnal communication, we used an SPI peripheral that can do both, here, SPI3. The SPI2
peripheral is used for JTAG, where TDI and TDO pins are used. The second SPI slave run as a full-duplex slave to ensure
synchronisation of the two peripherals.

When running in SWD mode, the SPI3 peripheral can be reconfigured to a serial receiver to provide the SWO ability.

## DUT communication

These signals are used by the hardware IO to the DUT, on the standard serial interfaces.

| Peripheral | Instance  |             Signal             |                Pin                 |             BGA              |              Testpoint               |       Description        |
| :--------: | :-------: | :----------------------------: | :--------------------------------: | :--------------------------: | :----------------------------------: | :----------------------: |
|   CLOCK    |  `MCO1`   |             `...`              |                 ``                 |              ``              |      Clock output for the DUT.       |
| I3C / I2C  |  `I3C1`   |         `SCL`<br>`SDA`         |           `PB8`<br>`PB9`           |         `A5`<br>`B4`         |           `TPxx`<br>`TPxx`           |   I3C master / slave.    |
|   USART1   | `USART10` | `TX`<br>`RX`<br>`RTS`<br>`CTS` | `PE3`<br>`PE2`<br>`PG14`<br>`PG13` | `A1`<br>`A2`<br>`A7`<br>`A8` | `TPxx`<br>`TPxx`<br>`TPxx`<br>`TPxx` | Full featured USART bus. |
|    CAN     | `FDCAN1`  |          `TX`<br>`RX`          |           `PE1`<br>`PE0`           |         `A3`<br>`A4`         |           `TPxx`<br>`TPxx`           |     FDCAN peripheral     |

## Miscellaneous

These signals describe all the others pins, for a lot of different functions that may not be linked together.

| Peripheral | Instance | Signal | Pin | BGA | Testpoint | Description |
| :--------: | :------: | :----: | :-: | :-: | :-------: | :---------: |
