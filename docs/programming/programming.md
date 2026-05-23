# Programming

All along this chapter, you'll see how can the device be accessed, and a technical description of any feature that could be usefull when working with it.
For more advanced topics about how the firmware is organized, you can check the **architecture** chapter, which explain choices and show software stack.

## Accessing the device

The device can be controlled from different ways, over different mediums:

| **Interface**     | **USB**                                  | **Ethernet**                                |
| :---------------- | :--------------------------------------- | :------------------------------------------ |
| **File transfer** | None\*                                   | FTP server                                  |
| **USART Bridge**  | VCOM 1                                   | None\*\*                                    |
| **Debugging**     | USB Debugger probe, CMSIS-DAP compatible | Remote debugger probe, CMSIS-DAP compatible |
| **Terminal**      | VCOM 0                                   | Telnet Shell                                |
| **SCPI**          | VCOM 0                                   | Dedicated SCPI port                         |

> - \* The file transfer can still be done by removing the SD card from the device. But, as a limitation from the filesystem we're using, files
>   can't be copied from the flash to the SD.
> - \*\* This feature can be emulated by the shell terminal. Some commands can perform IO, and thus this is possible. Speed may be affected.
