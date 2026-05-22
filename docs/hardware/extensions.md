# Extension boards

The whole project is based on different boards, including an extension board.
The latter one target different missions:

- Adapt the signal to the required usage (voltage, isolation, current...).
- Protect the main board, in case of failure of the DUT (short-circuit, over-voltage...).
- Be a devboard by itself, in the meaning, nothing prevent (that's even an handled case !) to put the target on the devboard, and play with it !

Therefore, it must be replacable, but also physically tied to the main board to protect them against mechanical damages.
To ensure that, we choosed to use the PCIe 4x connector, to provide both power and signals to this board. 
The form factor isn't compliant, as well as the pinout.

This connector was preferred, as it's able to use standard 1.6mm PCB, which only require fingers and an angle. This greatly reduce cost for custom boards, as
it won't require any costly option. From our checks, you can get a compatible board from JLCPCB starting at 25€ (4 layers + ENIG).

## Mechanical format

The board require to be in this format. The length that goes outside (L) can be extended beyond, at the condition:
- Your case can accept it
- The mechanical structure remain adequate for the load to be applied.

[ TODO : Export from altium ]

 ## Electrical consideration

There's two power rails :

| Rail       | Value                         | Current     | Host capacitance | Notes                                                |
| :--------- | :---------------------------- | :---------- | :--------------- | :--------------------------------------------------- |
| MASTER_VDD | Fixed to 3.3V                 | Up to 0.5 A | At least 10 uF   | Used to supply the onboard EEPROM and level shifters |
| DUT_VDD    | Variable between 0.6 and VUSB | Up to 4 A   | At least 100 uF  | Used to supply the test logic                        |

All signals that are going over the PCIe connector are referrenced in the MASTER_VDD domain.
DUT_VDD is only applicable after the outputs are adapted by buffer, or any logic circuits. 

## Pinout

The PCIe pinout is inspired by the standard PCIe, but vastly differ passed the notch. 
In any case, **DO NOT HOOK STANDARD PCIe BOARDS** (The layout make that impossible, but with extenders...).

Here the complete pinout :

| Pin       | Side A                                     | Side B                                 |
| :-------: | :----------------------------------------- | :------------------------------------- |
| **1**     | BOARD_PRESENT                              | DUT_VDD                                |
| **2**     | DUT_VDD                                    | DUT_VDD                                |
| **3**     | DUT_VDD                                    | DUT_VDD                                |
| **4**     | GND                                        | GND                                    |
| **5**     | TCK / SWCLK                                | MANAGEMENT_SCL                         |
| **6**     | TDI                                        | MANAGEMENT_SDA                         |
| **7**     | TDO / SWO                                  | GND                                    |
| **8**     | TMS / SWDIO                                | MASTER_VDD                             |
| **9**     | DUT_VDD                                    | DUT_RESET                              |
| **10**    | DUT_VDD                                    | GND                                    |
| **11**    | BUFFER_EN                                  | DUT_PRESENT (DUT must pull to DUT_VDD) |
| **NOTCH** | **NOTCH**                                  | **NOTCH**                              |
| **12**    | I3C_SDA                                    | I3C_SCL                                |
| **13**    | CLK                                        | GND                                    |
| **14**    | GND                                        | USB DP                                 |
| **15**    | GPIO PUSH_PULL 0                           | USB DM                                 |
| **16**    | DAC 0                                      | GPIO OPEN_DRAIN 0                      |
| **17**    | DAC 1                                      | GPIO OPEN_DRAIN 1                      |
| **18**    | GND                                        | GND                                    |
| **19**    | GPIO PUSH_PULL 1                           | CAN TX                                 |
| **20**    | GND                                        | CAN RX                                 |
| **21**    | ADC 0                                      | GPIO OPEN_DRAIN READ 0                 |
| **22**    | ADC 1                                      | GPIO OPEN_DRAIN READ 1                 |
| **23**    | SPI SS1                                    | SPI SS0                                |
| **24**    | GND                                        | SPI_MOSI                               |
| **25**    | SPI_MISO                                   | GND                                    |
| **26**    | SPI SCLK                                   | GND                                    |
| **27**    | USART1 RTS                                 | USART1 RX                              |
| **28**    | USART1 CTS                                 | USART1 TX                              |
| **29**    | USART2 RX                                  | GND                                    |
| **30**    | USART2 TX                                  | GND                                    |
| **31**    | GND                                        | USART3 RX                              |
| **32**    | GND                                        | USART3 TX                              |
