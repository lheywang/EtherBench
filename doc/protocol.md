# EtherBench Terminal & Binary Protocol Specification

This document define both interface for programming this tool. It support both commands, over a single session.

The first ones are the command line style ones, which are targetted to humans.
The seconds ones are the SCPI commands, which are more targetted to automated scripts and others cool stuff like that.

Commands types accepted, by interface :
 
| Interface        | SCPI | Command Line |
| ---------------- | ---- | ------------ |
| VCOM 0           | Yes  | Yes          |
| VCOM 1           | No   | No           |
| SSH (port 22)    | No   | Yes          |
| TELNET (port 23) | No   | Yes          |
| RAW (port 5025)  | Yes  | No           |

This enable some complex interractions with the device, while retaining a simple routing logic. Everything is handled by a pair process, which are responsible for low level hardware interraction. One parse the commands, the other execute.

## SCPI Commands
Input buffer (4 commands)
Output buffer (8 commands).
Policies : Ensure already present commands, returns error in case of overflow.

**CONFiguration** :
    VOLTage :
        level
        ?

**HARDware** : -> low level IO, for buses. A session must be openned for the stream to be available to any consummer process.
    **READ** :
        I2C? ADDR len
        SPI? len
        UART0? len
        UART1? len
        CAN? addr len

            CMD : read [target I2C|SPI|UART0|UART1|CAN] [addr]

    **WRITe** :
        I2C ADDR len #\[data\]
        SPI LEN #\[data\]
        UART0 len #\[data\]
        UART1 len #\[data\]
        CAN len #\[data\]

            CMD : write [target I2C|SPI|UART0|UART1|CAN] [addr] 

    **SPY** :
        I2C \[addr\] [DISAble]
        SPI [DISAble]
        UART0 [DISAble]
        UART1 [DISAble]
        CAN [DISAble]

            CMD : spy <--disable> [source I2C|SPI|UART0|UART1|CAN] [addr] 

**ANALog** : -> Low level Analog IO
    **TEMP** :
        ?
            CMD : temperature
    **INPUt** :
        ? 0 | 1
            CMD : analog-read --channel 0|1
    **WRITe** :
        voltage
            CMD : analog-write "value"

**FILEsystem** : -> simplified file systems. Higher performance copy methods are available.
    **CD** path
        CMD : cd "path"
    **LS**
        CMD : ls "path"
    **MKDIR** name
        CMD : mkdir "path"
    
    *[ONLY SUPPORTED OVER TERMINAL]*
        CMD : cat "file"

**PROGammation** : -> JTAG / SWD programming interface
    **CONNect** mode \[uart swd\]
        CMD : target-connect --mode SWD|JTAG
    **FLASh** mode file
        CMD : target-flash --mode SWD|JTAG "file"
    **VERIfy** mode file
        CMD : target-verify --mode SWD|JTAG "file"
    **READ** mode \[target file\]
        CMD : target-read --mode SWD|JTAG "file"
    **STATus** mode
        CMD : target-status --mode SWD|JTAG
    **DEVIce** mode
        CMD : target-device --mode SWD|JTAG "file"
    **DETEct** mode
        CMD : target-detect --mode SWD|JTAG "file"

**LOGGer** :
    **SD** :
        SUBScribe : source \[spy analog swo\]
        UNSUbscribe : source \[spy analog swo\]
    **TERMinal** :
        SUBScribe : source \[spy analog swo\]
        UNSUbscribe : source \[spy analog swo\]
    
    CMD : subscribe --target SD|TERM "source" 
    CMD : unsubscribe --target SD|TERM "source" 

**ACTIons** :
    ACT1 | ACT2 | ACT3:
        RESET
            CMD : reset-action --id 1|2|3 "cmd" 
        SET cmd (accept any string, command formatted (scpi or cmd). Triggered when pressed.
            CMD : set-action --id 1|2|3 "cmd" 

**SEQUences** :
    **RUN** file \[from flash\]
        CMD : run [file]

+ standard IEEE 488.2 commands (all known and response, but not implemented (ex, \*CAL?).