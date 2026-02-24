# Mechanical

## Placement

Leds ring, top PCB perhaps. Latteral screen for basic Info (IP...). (Oled, 128 x 32, slidding).

### Buttons
Placed on the side

- Go (user programmable)
- Stop (user programmable)
- reset (small).

### Screens
- Small I2C screen on a side

### Leds :

- Eth activity (Green / Yellow)
- Usb activity (Blue / Red)
- Flash activity (Orange / Green)
- Status (blink, green)

### Led ring :

- Deep Blue effect, as loading (boot and init)
- Yellow progress bar (Flash progress)
- Magenta progress bar (Test sequence progress, in number of steps, luminosity of each led as sub values)
- Green flashing : End of sequence, PASS
- Red flashing : End of sequence, FAIL
- Cyan breathing : Idle, nothing is running actually.
- Red flashing (2 fast, 2 slow) Error, need to reboot.
- Yellow breathing : Active debugging session

## Board placement

MAIN pcb (MCU + IO + Eth + USB), on top (leds + right angled buttons + i2c screen) + logos.

Assembled with headers and screens (sides).

Target size : 100m (W) x 100 mm (L) x 20 mm (H).
Nice case, with cool effects.