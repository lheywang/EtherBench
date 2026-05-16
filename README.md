# EtherBench

EtherBench is an open hardware debugger based on three components:
- An hardware probe, based on an STM32H5
- A gui app,based on Qt
- A C software library, to extend the debug ability.

The goal is to be able to program, test and debug MCUs and MPUs without hassle.

## Hardware : 

This too is built around an STM32H563 MCU which act as the core of the probe.

On the device edge, a set of IO are available, which include : 
- 1x full featured USART (with optional flow control lines).
- 1x minimal usart (only serial lines).
- 1x I2C, up to 1 Mbps.
- 1x SPI, up to 50 mbps.
- 1x CAN.
- 1x Clock (derived from the MCU clock tree).

Some analog features :
- 2x 12 bits, analog input.
- 1x 12 bits, analog output.

All of these features are behind an isolation barrier, ensuring the device safety. A short circuit on the tested board won't damage the core, and by extension, the host.

To extend theses options, some options for the host side: 
- 1x SD card, to store logs.
- 1x 128 MB of onboard flash.
- 1x 100 Mb Ethernet port.
- 1x USB-C device.
- 2X USB-A host.

The memory can be used, without any distinctions to store any relevant data: Firmware to be flashed, logs, or test sequences.

The USB-C port is used for power, a 10W charger is required, where a 15W one is recommended.

Both the USB-C and Ethernet port may be used for communication with the host. Prefer Ethernet, as it's isolated and can provide an higher bandwith.

All of that fit within a 110 x 110 mm case, which hold all of the electronic circuit over two layer of PCB. The main one, a 6 layer, and the top one, a two layer board.

## Communications

The board has two sets of IO, as USB and Ethernet. Any features can be used from both, but for the greatest experience, both can be used.

Once connected, the device expose itself as a lot of device :

### USB

On the USB side, three peripherals are exposed:
- EtherBench-Terminal: A VCOM port, used as a terminal to send commands.
- EtherBench-Bridge: Another VCOM port, but reserved for the UART0 communication. Most basic feature here.
- EtherBench-Probe: A CMSIS-DAP compatible probe, ready to be used from any programmer software.

### Ethernet

On the network side, the stack is a bit dlfferent. No devices are shown, but multiple ports are open:

- 20 & 21: An FTP server, to access the file systems.
- 23: A Telnet console, to be used within command line interface. 
- 5025: An SCPI compliant device.
- XX: A Streaming port, can be configured. Used to transfer large volume of data without the hassle of SCPI commands.

### Consoles

As previously showned, multiple consoles are available. These are terminals that could be openned by users to interract with the device. All of them are strictly identical.

### Routers

Any IO can be muxed to any sink of data, including file systems. This can be configured from the command line.

| Technology    | Bus                         |
| :------------ | :-------------------------- |
| File transfer | FTP (or unplug the SD card) |
| USART Bridge  | Both, USB preferred         |
| Debugging     | Both                        |
| Terminal       | Both, Ethernet preferred   |


This enable advanced features like deferred logging, or different outputs.

## Software :  

There's quite a lot of software on this project, at different layers.

### Embedded

First, the embedded C/C++ app. This one runs on the probe, on the STM32 flash. It's based on ThreadX with extensions, and manage everything:

- NetXDuo: Network stack, including DHCP and server.
- USBX: USB stack, that handle the VCOM and custom class.
- LevelX: Flash wear leveling management.
- FileX: Filesystems

Some functions are also reused from the C standard library, thus file handling is possible within this project. The memory is shown after.

On top of that, a set of different tasks communicate with others to provide all the features. A full graph is available right under that paragraph.

[todo export drawio]

Each of these are designed to provide performance while remaining simple to maintain.

All of that code is available on the /src folder of that repo. Build and debug configurations are also available.

### Desktop App

A desktop app, wrote in pure C++ to provide graphics features to the project. While it's designed to mainly operate with the probe, its not designed to be exclusive. No commands are hardcoded.

The app provide a GUI to most settings and features, while also providing data analysis features, from stored buffers. This include:
- A serial interface gui
- A memory buffer management gui
- A data analysis tool
- Probe configuration menu.

It's designed to use the capacities of our desktop pc to provide an higher level of features, that could not be possible on an embdded app. 

The GUI can be used as a stabdadone tool, it does not require any board to be wired.

### Library

The library is a fully optionnal brick, that can be placed between each. It's based on pure C implementation, to be runned on any architecture that exists. 

Can be used to format messages and buffer before sending them over any buses. The desktop app will then be able to parse them, and provide more infos than just the value itself, such as timestamps, formats and so on.

### Scripting

There's two layer of scripting available on the tool. One that run on the device, and one from the desktop app.

#### Device scripts 

The device can execute simple sequences of opererations, that can be triggered from any inputs, including a button press.

The scripts are quite limited, as it does not support advanced conditions and advanced programming methods.

These are aimed at simple series of operations, for exemple the programming of a chip. The core goal is the timing constraints, which are very tight here.

Only basic conditions are supported. If you're looking at more advanced options, you could else check the SCPI documentation, for an 100% integration with any software, else you can check at the desktop programming options.

#### Desktop scripts

The GUI App provide python interpreter option, from an isolated thread. It include a library by default to provide IO features from the device without typing complex commands.

This enable more complex conditions, loop, and computations. But, you're loosing the timings constraints as you're going through a lot of layers. These scripts can call device scripts to offer an alternative.

Generally, I greatly recommand using this method over the first one.

## Memory map

Finally, here the memory map from that device: 

### SD

| Volume | Size | Usage                               |
| :----- | :--- | :---------------------------------- |
| /sd/   | All  | Outputs (logs, measures, reports... |

### Flash

| Volume      | Size    | Usage                                                               |
| :---------- | :------ | :------------------------------------------------------------------ |
| /settings/   | 128 Ko  | Device config. Binaru format only.                                 |
| /backtrace/ | 128 Ko  | Target crash dump (if any). Binary format only.                                        |
| /flash/     | 127 Mo  | Firmwares to be flashed, sequences. Anything that may be executed.  |


