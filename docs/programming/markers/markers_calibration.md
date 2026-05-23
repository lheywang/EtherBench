# Calibration values

The calibration optionnal page target application where the analog input has been adapted for any reason, and some corrections must be applied.
As a reminder, the internal ADC of the ST MCU is used, therefore, for precise analog IO, a specialized tool shall be used.

## Page structure

| **Offset** | **Size (Bytes)** | **Description**                  |
| :--------: | :--------------: | :------------------------------- |
|   `0x00`   |      **2**       | Pages marker, constant to 0xEBB4 |
|   `0x02`   |      **2**       | Page CRC                         |
|   `0x04`   |      **4**       | ADC 0 Offset (float)             |
|   `0x08`   |      **4**       | ADC 1 Offset (float)             |
|   `0x0C`   |      **4**       | ADC Gain (float)                 |
|   `0x10`   |      **4**       | DAC 0 Offset (float)             |
|   `0x14`   |      **4**       | DAC 1 Offset (float)             |
|   `0x18`   |      **4**       | DAC Gain (float)                 |
|   `0x1C`   |      **2**       | Calibration year                 |
|   `0x1E`   |      **1**       | Calibration month                |
|   `0x1F`   |      **1**       | Calibration day                  |

## Yaml arguments

When using the automated page builder, available on the EtherBenchProbe repo, all of this page shall be placed under the calibration tag.
Then, these keys are searched:

|   **Key**   | **Format**                 | **Default value** |
| :---------: | -------------------------- | ----------------- |
| adc0_offset | Any SI value (12mV, 1V...) | `0V`              |
| adc1_offset | Any SI value (12mV, 1V...) | `0V`              |
|  adc_gain   | Float                      | `1.0`             |
| dac0_offset | Any SI value (12mV, 1V...) | `0V`              |
| dac1_offset | Any SI value (12mV, 1V...) | `0V`              |
|  dac_gain   | Float                      | `1.0`             |
|    year     | Integer (16 bits)          | `2026`            |
|    month    | Integer (8 bits)           | `1`               |
|     day     | Integer (8 bits)           | `1`               |

The present of any key will trigger the build of the page. Missing keys are going to be filled with the default value.
