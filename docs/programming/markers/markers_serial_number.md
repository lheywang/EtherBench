# Serial Number

The serial number page can be used when more than one board may be used, therefore the need to identify them is expressed.
This page can store informations that are specific to the board, rather than the standard string which is too generic

## Page structure

| **Offset** | **Size (Bytes)** | **Description**                  |
| :--------: | :--------------: | :------------------------------- |
|   `0x00`   |      **2**       | Pages marker, constant to 0xEBB5 |
|   `0x02`   |      **2**       | Page CRC                         |
|   `0x04`   |      **4**       | Serial number (free format)      |
|   `0x08`   |      **20**      | Manufacturer string              |
|   `0x1C`   |      **2**       | Fabrication year                 |
|   `0x1E`   |      **1**       | Fabrication month                |
|   `0x1F`   |      **1**       | Fabrication day                  |

## Yaml arguments

When using the automated page builder, available on the EtherBenchProbe repo, all of this page shall be placed under the serial_number tag.
Then, these keys are searched:

|       **Key**       | **Format**                        | **Default value** |
| :-----------------: | --------------------------------- | ----------------- |
|    serial_number    | Integer (32 bits)                 | `0xDEADBEEF`      |
| manufacturer string | Any char array (20 character max) | `EtherBenchLabs`  |
|        year         | Integer (16 bits)                 | `2026`            |
|        month        | Integer (8 bits)                  | `1`               |
|         day         | Integer (8 bits)                  | `1`               |

The present of any key will trigger the build of the page. Missing keys are going to be filled with the default value.
