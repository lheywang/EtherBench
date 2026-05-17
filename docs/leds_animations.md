# EtherBench LED Ring Animation Specification

**Hardware:** 10x WS2812B LEDs arranged in a circle.
**Update Rate:** 50 Hz (20ms) via DMA/Timer.

## 1. System States & Animations

### Boot Process / Initialization
* **Animation:** "Cylon / Radar Spin"
* **Description:** A single bright Blue pixel spins around the 10-LED circle rapidly, leaving a fading trail of 3 pixels behind it.
* **Color:** Cyan / Blue (`#22F2D6`)
* **Trigger:** Power on until RTOS threads are fully initialized and IP address is acquired.

### System Ready / Idle
* **Animation:** "Breathing"
* **Description:** All 10 LEDs slowly pulse on and off simultaneously using a sine wave function.
* **Color:** Dim Yellow (`#FDFF91`)
* **Timing:** 3-second full cycle (1.5s fade up, 1.5s fade down).
* **Trigger:** RTOS is idle, no active network connections, no target board connected.

### Active Target Debugging (CMSIS-DAP)
* **Animation:** "Solid Activity"
* **Description:** The ring show a progress status of the flash interface. Restart from 0 when in debugging session.
* **Color:** Orange (`#FFBF00`)
* **Trigger:** OpenOCD connects and claims the USB interface.

### Target Crashed (CMSIS-DAP)
* **Animation:** "Solid Activity"
* **Description:** All 10 LEDs blink on and off rapidly at 5Hz (100ms on, 100ms off). Only for the device error (not the DUT).
* **Color:** Violet (`#C9006F`)
* **Trigger:** OpenOCD connects and claims the USB interface.

### Sequence running
* **Animation:** "Progress bar"
* **Description:** The ring show a progress status of the sequence.
* **Color:** Yellow (`#E6DC20`) / Violet (`#601AED` / `#9B71F0` / `#C6B1F2`)
* **Trigger:** User start a sequence. Yellow for custom one, Violet if triggered from the actions buttons.

### Sequence Ended
* **Animation:** "Breathing"
* **Description:** All 10 LEDs slowly pulse on and off simultaneously using a sine wave function.
* **Color:** Green (`#34BA4A`) / Red (`#C4314C`)
* **Trigger:** Sequence has ended. Here the results.

### Hard Error / Fault
* **Animation:** "Strobe"
* **Description:** All 10 LEDs blink on and off rapidly at 5Hz (100ms on, 100ms off). Only for the device error (not the DUT).
* **Color:** Pure Red (`#E02926`)
* **Trigger:** HardFault, Ethernet disconnect, or Storage failure.
