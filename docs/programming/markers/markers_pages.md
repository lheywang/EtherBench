# Pages

| **Offset** | **Size (Bytes)** | **Description**                  |
| :--------: | :--------------: | :------------------------------- |
|   `0x00`   |      **2**       | Pages marker, constant to 0xEBB1 |
|   `0x02`   |      **2**       | Page CRC                         |
|   `0x04`   |      **4**       | Optionnal page 0                 |
|   `0x08`   |      **4**       | Optionnal page 1                 |
|   `0x0C`   |      **4**       | Optionnal page 2                 |
|   `0x10`   |      **4**       | Optionnal page 3                 |
|   `0x14`   |      **4**       | Optionnal page 4                 |
|   `0x18`   |      **4**       | Optionnal page 5                 |
|   `0x1C`   |      **4**       | Optionnal page 6                 |

Up to 7 pages can be added, maxing out at 8 optionnal pages in total.

## Yaml arguments

This page cannot be added by the yaml file. The script will add it, if required. No user action required.
