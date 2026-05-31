# Board manager

The board manager process is one of most important thread to be runned, as it rules all behaviors of the board, without the user knowing it.
Therefore, under it's own responsability are placed :

- The I2C screen
- The USB Hub
- The DUT regulator
- The daughter board EEPROM
- The temperature sensors

That's done because all of them share a single bus, the I2C peripheral. Thus, we don't need heavy mutex for each access.

To remains coherent within the architecture paradigm we choosed, this thread remains quite independant. Except requests for screen messages, and
DUT voltage, it's isolated from the other.

## Life cycle

This thread is among the first to be started. Once launched, it'll start initializing all the peripheral, essentially the USB Hub. Then, it'll loop at
a frequency of 100 Hz to adjust the voltage of the DUT and monitor values.

This thread can't be stopped nor paused.

## Battery emulation mode

If enabled, the DUT voltage will follow the following equation, derived from the Sheperd equation.
The ony different is the lack of the $$R \cdot I$$ term, which can't be properly modeled with a discrete controller. 
It corresponds to the ESR value of the resistance, the user must place it physically, in series with the power supply.

$$
V_{batt} = E_0 - K \cdot \left(\frac{Q}{Q - it}\right) \cdot it + A \cdot e^{-B \cdot it}
$$
