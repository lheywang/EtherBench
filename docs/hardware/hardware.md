# Hardware

EtherBench, at least the probe is designed around an assembly of three PCB :

* One master board, with six layers. It host all the complex functions of the device.
* One top board, with the leds and basic leds features.
* Two lateral boards, with buttons and the screen.

The two later ones are done with a two layer boards, as there isn't any high speed signals nor complex requirements.
Therefore, the cost of the device remains accessible.

The electrical part fit within a 110 x 110 mm boards assembly.

## Master board

The master board is designed around

> **Note**
> While the global concept of the boards is done, the specific details aren't. Thus, no boards / assemblies / schematic are going to be added. 
> They'll be once finished.

## Top board

The top board act as a user interface more than a functionnality board. it comports:

* A ring led, as the main interface with the user
* Some status leds

### Led ring

The led rings, based over 20 WS2812 leds show the user animations, and statuses. 
This replace a complex gui with simpler animations. The GUI is then sent back over buses to the host computer.

Multiple animations can be shown :

| Animation          |                              Color                               | Description                                                                                                      | Meaning                                                                                     |
| :----------------- | :--------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------ |
| Cylon / Radar Spin |                            `#22F2D6`                             | A single bright Blue pixel spins around the 10-LED circle rapidly, leaving a fading trail of 3 pixels behind it. | Power on until RTOS threads are fully initialized and IP address is acquired.               |
| Breathing          |                            `#FDFF91`                             | All 10 LEDs slowly pulse on and off simultaneously using a sine wave function.                                   | RTOS is idle, no active network connections, no target board connected.                     |
| Solid Activity     |                            `#FFBF00`                             | The ring show a progress status of the flash interface. Restart from 0 when in debugging session.                | Software has connected and claimed the USB interface.                                       |
| Blink Activity     |                            `#C9006F`                             | All 10 LEDs blink on and off rapidly at 5Hz (100ms on, 100ms off). Only for the device error (not the DUT).      | DUT does not respond anymore (crash ?)                                                      |
| Progress bar       | Yellow : `#E6DC20` or Violet : `#601AED` / `#9B71F0` / `#C6B1F2` | The ring show a progress status of the sequence.                                                                 | User start a sequence. Yellow for custom one, Violet if triggered from the actions buttons. |
| Breathing          |               Green : `#34BA4A` or Red : `#C4314C`               | All 10 LEDs slowly pulse on and off simultaneously using a sine wave function.                                   | Sequence has ended. Here the results.                                                       |
| Strobe             |                            `#E02926`                             | All 10 LEDs blink on and off rapidly at 5Hz (100ms on, 100ms off). Only for the device error (not the DUT).      | HardFault, Ethernet disconnect, or Storage failure.                                         |

### Leds

In addition of the main ring leds, there's 8 leds placed on the side.
These show the user informations about what's being currently transfered.

| Leds                               | What it means                                          |
| :--------------------------------- | :----------------------------------------------------- |
| Ethernet activity (Green / Yellow) | There's currently Ethernet trafic                      |
| Usb activity (Blue / Red)          | There's currently USB trafic                           |
| Flash activity (Orange / Green)    | There's currently memory IO, especially to the SD card |
| Status (blink, green)              | I'm alive !                                            |

## Side boards

The side boards are used as user inputs, and thus contain essentially buttons. A small I2C screen is added, 
to display basic informations on it, such as the granted IP in case of the DHCP attribution.

For each EtherBench probe, there's two of these boards, on each side.

|   Feature   | Right board | Left board |
| :---------: | :---------- | :--------- |
| OLED screen | 🚫           | ✅          |
|  Go button  | 🚫           | ✅          |
| Stop button | 🚫           | ✅          |
|    Reset    | ✅           | 🚫          |

### OLED screen

The onboard screen is used to show specific infos, that can't be reported in any other ways. This include, as 
explained before the IP, because at this point, your not connected.

It's also used to show additionnal infos, such as:

* Sequences info (what failed ?)
* Error codes, to get more specific infos (rather than a generic red flash)
* Progressions
* Custom infos, from the sequence support.

### Go / Stop button

These buttons are used as trigger for specific, sequence related actions.

Therefore, it's possible to start or stop a sequence that can be execute from within the flash, in total autonomy.

### Reset button

The button will perform an hardreset of the device. That's why it's quite "hard"

