# Board name

The name page enable to include a human description string to be included, thus making it easier to show.
If available, it's shown on the console.

| **Offset** | **Size (Bytes)** | **Description**                  |
| :--------: | :--------------: | :------------------------------- |
|   `0x00`   |      **2**       | Pages marker, constant to 0xEBB3 |
|   `0x02`   |      **2**       | Page CRC                         |
|   `0x04`   |      **28**      | ASCII coded name.                |

## Yaml arguments

When using the automated page builder, available on the EtherBenchProbe repo, only the name key is required to add that page.

| **Key** | **Format**                                                            | **Default value** |
| :-----: | --------------------------------------------------------------------- | ----------------- |
|  name   | Any text. Only 28 first characters are used. No termination required. | `None`            |
