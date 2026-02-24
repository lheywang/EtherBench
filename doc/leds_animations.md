# EtherBench LED Ring Animation Specification

**Hardware:** 10x WS2812B LEDs arranged in a circle.
**Update Rate:** 50 Hz (20ms) via DMA/Timer.

## 1. System States & Animations

### Boot Process / Initialization
* **Animation:** "Cylon / Radar Spin"
* **Description:** A single bright Blue pixel spins around the 10-LED circle rapidly, leaving a fading trail of 3 pixels behind it.
* **Color:** Cyan / Blue (`#00FFFF`)
* **Trigger:** Power on until RTOS threads are fully initialized and IP address is acquired.

### System Ready / Idle
* **Animation:** "Breathing"
* **Description:** All 10 LEDs slowly pulse on and off simultaneously using a sine wave function.
* **Color:** Dim Yellow (`#FFFF00` to `#707000`)
* **Timing:** 3-second full cycle (1.5s fade up, 1.5s fade down).
* **Trigger:** RTOS is idle, no active network connections, no target board connected.

### Active Target Debugging (CMSIS-DAP)
* **Animation:** "Solid Activity"
* **Description:** The ring show a progress status of the flash interface. Restart from 0 when in debugging session.
* **Color:** White (`#FFFFFF`)
* **Trigger:** OpenOCD connects and claims the USB interface.

### Hard Error / Fault
* **Animation:** "Strobe"
* **Description:** All 10 LEDs blink on and off rapidly at 5Hz (100ms on, 100ms off).
* **Color:** Pure Red (`#FF0000`)
* **Trigger:** HardFault, Ethernet disconnect, or Storage failure.
