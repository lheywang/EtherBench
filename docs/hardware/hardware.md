# Hardware

EtherBench, at least the probe is designed around an assembly of three PCB :

- One master board, with six layers. It host all the complex functions of the device.
- One top board, with the leds and basic leds features.
- Two lateral boards, with buttons.

The two later ones are done with a two layer boards, as there isn't any high speed signals nor complex requirements.
Therefore, the cost of the device remains accessible.

The electrical part fit within a 110 x 110 mm boards assembly.

## Master board

The master board is designed around

!!! note "Unfinished spec"
    This document present reflexions about non finished designs. Therefore, details may be changed without notice.

## Top board

The top board act as a user interface more than a functionnality board. it comports:

- A ring led, as the main interface with the user
- Some status leds
- An I2C screen

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

### Led

In addition of the main ring leds, there's a single led, that blink when the device is powered on. 
It's only used to show that the system is alive.

### Screen

A small I2C screen is added on the top board, and is used to show the user basic info about the device:

- Can is remove the SD
- What's it's IP
- Is there something running currently ?
- Sequences info (what failed ?)
- Error codes, to get more specific infos (rather than a generic red flash)
- Progressions
- Custom infos, from the sequence support.

The integrated UI remains quite simple, as the device is designed to be operated remotely, over Ethernet or USB.

## Side boards

The side boards are used as user inputs, and thus contain essentially buttons. 

For each EtherBench probe, there's two of these boards, on each side.

On the left side, the reset button is added. It enable to send to the MCU a reset request, which will be treated once the condition permit it.
This mean before resetting, the network sessions will be closed, and the debugger sessions will be closed.

On the right side, there's three buttons, referred as ACTx, from 0 to 2. These can be freely programmed by the user, to do anything they want.
By default, the ACT0 and ACT1 are unused, and ACT2 is the STOP button, to stop a currently running operatio?

### Go / Stop button

These buttons are used as trigger for specific, sequence related actions.

Therefore, it's possible to start or stop a sequence that can be execute from within the flash, in total autonomy.

### Reset button

The button will perform an hardreset of the device. That's why it's quite "hard"
