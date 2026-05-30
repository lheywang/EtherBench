# Battery values

The battery emulation mode enables the test of battery powered DUTs. The provided voltage will then follow an approximated curve, to simulate it.
The ESR value is only here for display, as it's impossible to sample all current transients to properly model it.
For precise tests, add that resistance to your daughterboard.

## Page structure

| **Offset** | **Size (Bytes)** | **Description**                                                       |
| :--------: | :--------------: | :-------------------------------------------------------------------- |
|   `0x00`   |      **2**       | Pages marker, constant to 0xEBBF                                      |
|   `0x02`   |      **2**       | Page CRC                                                              |
|   `0x04`   |      **4**       | Battery tag                                                           |
|   `0x08`   |      **4**       | Capacity (mAh) [Q] (float)                                            |
|   `0x0C`   |      **4**       | Base voltage (V) [E0] (float)                                         |
|   `0x10`   |      **4**       | Drain speed factor [K] (V) (float)                                    |
|   `0x14`   |      **4**       | Overvoltage value (V) [A] (float)                                     |
|   `0x18`   |      **4**       | Overvoltage drain speed (V) [B] (float)                               |
|   `0x1C`   |      **4**       | ESR (Ohm) (float) (unused for simulation, only for report generation) |

### Battery tags

The embedded firmware include pre-configured batteries, that can be directly emulated without any user configuration.
Any value that is passed on top of that will be added to the loaded one. Any unknown tag will use as base all zeroes.

| **Type**           |   **Tag**    | **Capacity** | **Base voltage** | **Drain speed** | **Overvoltage** | **Overvoltage drain speed** | **Recommended ESR** |
| :----------------- | :----------: | :----------: | :--------------: | :-------------: | :-------------: | :-------------------------: | :------------------ |
| `Li-Po` / `Li-ion` | `0x10010001` |   2200 mAh   |      3.75 V      |     0.0075      |     0.350 V     |             25              | 2-5 mOhm            |
| `LiFe-PO4`         | `0x10010002` |   3500 mAh   |      3.25 V      |     0.0020      |     0.150 V     |             70              | 3-4 mOhm            |
| `CR2032`           | `0x10020001` |   215 mAh    |      3.00 V      |     0.2000      |     0.075 V     |             135             | 20 Ohm              |
| `NiMH`             | `0x10020002` |   2000 mAh   |      1.28 V      |     0.0035      |     0.159 V     |             40              | 100 mOhm            |
| `Alkaline`         | `0x10020003` |   2000 mAh   |      1.50 V      |     0.0075      |     0.050 V     |             10              | 100 mOhm            |

## Yaml arguments

When using the automated page builder, available on the EtherBenchProbe repo, all of this page shall be placed under the battery tag.
Then, these keys are searched:

|         **Key**         | **Format** | **Default value** |
| :---------------------: | ---------- | ----------------- |
|           tag           | Integer    | 0                 |
|        capacity         | Float      | 1000              |
|      base_voltage       | Float      | 3.7               |
|      drain_factor       | Float      | 0.005             |
|       overvoltage       | Float      | 0.5               |
| overvoltage_drain_speed | Float      | 10                |
|           ESR           | Float      | 0                 |

The present of any key will trigger the build of the page. Missing keys are going to be filled with the default value.
