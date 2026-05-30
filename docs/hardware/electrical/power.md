# Power

The EtherBench project features a dynamic power management system designed to handle a wide range of input voltages and currents.
Because features are structurally limited by the available source power, users must understand the operating modes before any operation.

This constraint particularly affects the Ethernet section and the ARGB LED matrix, which can consume hundreds of milliamperes.
This thermal and power budget cannot be sustained when the input power source is too weak.

## Power profiles

Therefore, the following matrix is applied:

| **Power delivery profile** | **USB** | **Ethernet** | **Led luminosity\*** | **Maximal DUT Power\*\*** |
| :------------------------: | :------ | :----------- | :------------------- | :------------------------ |
|         `20V @ 3A`         | Enabled | Enabled      | 100 %\*              | 48 W                      |
| `20V @ 2.25A` / `15V @ 3A` | Enabled | Enabled      | 100 %\*              | 35 W                      |
|         `12V @ 3A`         | Enabled | Enabled      | 75 %\*               | 25 W                      |
|         `9V @ 3A`          | Enabled | Enabled      | 50 %\*               | 18 W                      |
|         `5V @ 3A`          | Enabled | Enabled      | 33 %\*               | 7.5 W                     |
|        `5V @ 1.5A`         | Enabled | Enabled      | 20 %\*               | 3.5 W                     |
|        `5V @ 0.5A`         | Enabled | Disabled     | Disabled             | 1 W                       |

> \* LED Luminosity: Can be overridden in software. The effective brightness will always be the lowest value between the user configuration and the hardware
> profile limit.

> \*\* Maximal DUT Power: Represents the theoretical maximum power budget assuming ideal efficiency. Since the PCIe slot physical current limit is capped at
> 4.5A (up to 12V), the highest DUT power levels can only be achieved with active buck-boost circuitry on the extension board. On the default model, the DUT
> power is strictly capped at 15W under 3.3V.

## Legacy USB-A operation

The `5V @ 0.5A` profile represents the baseline USB 2.0 specification. This mode is typically active when using legacy USB-A to USB-C cables or standard PC ports.
To preserve a reasonable power margin for the DUT and prevent host port overcurrent shutdowns, the Ethernet PHY is held under hardware reset and the ARGB LEDs are
powered off.

Since modern PC ports can often supply more than 500 mA without advertising it via Type-C analog signaling (or over legacy cables), a dedicated CLI command allows
the user to manually override the current profile (valid for 5V profiles only).

> Overriding the USB power profile bypasses hardware protections and shall be done at the user's own risk.

For exigeant or high-power DUTs, an external power supply can be wired directly to the extension board to bypass USB limitations. In that case, the internal
regulator can be simply turned-off (Request of a 0.0V).

## Power algorithms

Internally, a dedicated power management thread monitors and configures the sub-systems at 10 Hz. The values shown in the profile matrix are deliberately
conservative, assuming a worst-case simultaneous consumption on the internal 3.3V and 5.0V rails.

In real-world scenarios, the infrastructure consumption is much lower. Therefore, the internal control loop dynamically allocates the unused residual
power to the DUT in real-time.

All analog measurements (from the INA232 system monitor and the DUT ADC) are filtered using a DSP filter to prevent edge-triggering or oscillation during
rapid load transients. Power budgets are stable and managed linearly.

## Power sequencing

When the power is first applied (by the two CC1 and CC2 resistors on the USB-C socket), the primary, 5V regulator start it's operation once the input has reached 4.5V\*. Once the first regulator as reached
92% of it's nominal voltage, the secondary 3.3V regulator start it's operation.

After the 3.3V rail is released, the STM32 MCU can start booting, and executing the startup sequence. Once done, the DUT will be identified, and parameters will be applied. The DUT dedicated regulator will then start it's operation.
