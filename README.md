# EtherBench

An integrated tool to provide advanced debugging and testing function, over a standard SSH remote connection !
It only require an USB port to be powered.

## Hardware : 

This tool, built around an STM32H563 MCU, which provide host features (SSH / SCP over Ethernet or WiFi, USB), 
as well as low level features : 
- 1x full featured USART (with flow control lines).
- 1x minimal usart (only serial lines).
- 1x I2C, up to 1 Mbps.
- 1x SPI, up to 50 mbps.
- 1x CAN.
- 1x Clock (derived from the MCU clock tree).

Some analog features :
- 2x 12 bits, 400 kS/s analog input, buffered.
- 1x 12 bits, analog output.

Finally, some memory : 
- Up to 32 GB of SD card, to store logs.
- 256 MB of onboard flash, to be able to be used as a standalone tool (can store firmware inside it).

All of this stuff fit into a 110 x 110 mm case, which include : 
- 2W power supply, from the USB to the main connector to the isolated highland.
- Isolation of the DUT, with configurable voltages, down from 1.8V to 5V (power supply can go down to 900mV).
- Intgrated USB Hub, to be able to wire another device to it (slave device, or any USB peripheral).
- Multiple leds, to show the user statuses.

## Software :  

What would be this tool without it's software ? Nothing.

The tool include different access ports :
- 2x USB VCOM, directly from the hardware 
- 1x USB VCOM, as a terminal
- 1x USB MCS, to copy firmware and read logs.
- 1x USB Debug probe, compatible with the industry standards.
- 1x SSH server
- 1x Remote debugger server, to be able to integrate the tool into standard IDEs.

All of them are able to read from any ports, and write to any (in the limit of the mutexes).

Additionally, the tool enable to follow test sequences, which include chip programming directly onboard, 
and produce logs and test reports on the SD card, without any host needed. A single button press, and here we go !

You can perfectly imagine a world where you wire the DUT, press a single button, wait, and see the result. The DUT
is flashed, and tested. This include monitoring serial logs for you !
