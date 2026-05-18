# Installing

As the project is based over three software components, installing can't be done with a single installer.
Only the Firmware is required for the device to be working, all other are add-ons.

## Embedded Firmware

1. You'll need a copy of the embedded firmware. The later one can be obtained from two sources:

    * Downloading a built firmware, on the [releases](https://github.com/lheywang/EtherBenchFirmware/releases).
    * Building your own, with the [STM32Cube](https://www.st.com/en/development-tools/stm32cubeide.html) environnement.

    For most user, I recommend the first option.


2. Then, we need to program the chip on the board. Any tool can be used, such as [CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html), 
    which can use the USB link to upload the firmware.

Alternatively, there's SWD pins available, thus, any USB-SWD probes can be reused.

3. Once done, the board shall come alive. If that's the case, you'r done for the firmware.

## Desktop Application

1. You'll need the installer, for the right exploitation system. You can download them on the [releases](https://github.com/lheywang/EtherBenchApp/releases). pages.

2. Run the installer. 
   
3. Done

Alternatively, you can build the software from sources, over the repo.

## Software library

The software library is actually a single header file, that provide abilities for the tool to send data in a known format to the App.
This expand the abilities of the App without costing that much.

There's no installation, as you copy that file into your project, include it, and build with your usual toolchain. That's all !
