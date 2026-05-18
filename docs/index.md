# Introduction

## What's EtherBench ?

Etherbench is a platform, built arround a lot of different projects, designed to make debugging and testing easier, without requiring costly tools.

While it provides basic debugger features, according to the [ARM CMSIS-DAP](https://arm-software.github.io/CMSIS-DAP/latest/) specification, over the two standard buses:
* [SWD](https://developer.arm.com/documentation/101761/1-0/Debug-and-trace-interface/Serial-Wire-Debug-signals) : Serial Wire Debug, common for MCUs
* [JTAG](https://developer.arm.com/documentation/101761/1-0/Debug-and-trace-interface/JTAG-signals) : Joint Test Action Group, common for FPGAs and MPUs.

It also provides standard buses, to perform most of the IO a chip can do, within a single device. This include:
* 2 x USART buses, up to 20 Mbaud. One of them include the modem features (RTS and CTS signals).
* 1 x SPI bus, up to 50 Mbaud.
* 1 x I2C bus, up to 4 MHz.
* 1x CAN bus

And, some very basic analog features:
* 2 x Analog inputs, up to 16 bits (emulated).
* 1 x Analog Output.

All of this stuff is isolated from the host, thus even in case of failure on the DUT side, your PC remains safe. 

To interract with the device, multiple options are offered:
* 100 Mbps Ethernet port (including DHCP)
* 12 Mbps USB port (behind a 480 Mbps hub, to wire others devices !).

Both options are similar in terms of features.

## Why ?

I've built this project, because I was tired to accumulating probes on my desk. One for the ST's, one for the FPGA, and so on.
Therefore, I've looked into different projects, such as [this one](https://github.com/saahinduran/STM32-JTAG-Emulator-). 
But, it wasn't complete, and didn't like the complete implementation, so, I've just rewrote my own implementation, with the latest features available.

The project then started as, and what if I add a USB-USART bridge to it ? And, wait, can't I also add an Ethernet port ? Now, we're here, reading 
the project documentation...

## Highlights

All of those aspects are detailed within their associated pages. Here a rapid tour of the horizon:

* High performance hardware
  * STM32H5 MCU, providing all the features of the probe
  * Isolated PCB, ensuring safety of your designs.
* Broad range of communications
  * Ethernet 
  * USB
  * SDMMC
* Easy to get hands on
  * Comprehensive leds signals
  * Standard interfaces

## More infos ? 

There's a lot that isn't documented here. Please check all the subsections, or download the PDF document !

- Installing the device
- Hardware schematic and details
- Programming guides
- Examples
- Software architecture
