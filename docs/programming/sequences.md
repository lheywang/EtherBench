# Sequences

Sequences are a big part of the Etherbench project. A lot of steps require some form of sequencing.
Currently, there air two options to address these requirements:

* Internal sequencing
* External sequencing

The first one is executed on the device, thereby providing the fastest responses. This is also the most limited option, as only very simple structures are possible.
The latter one is running on any host computer. It's response times are dependent on the IO method used, and software stacks. 
Any algorithm can be implemented here.Any algorithm can be implemented here

## Internal sequencing

The internal sequences only support five instructions:

| Instruction | Syntax               | Description                                                                                              | Example               |
| :---------- | :------------------- | :------------------------------------------------------------------------------------------------------- | :-------------------- |
| `execute`   | `execute <command>`  | Execute the passed SCPI string, as it was passed by any IO.                                              | `execute *IDN`        |
| `if`        | `if <string>`        | Evaluate the condition, and, if true, execute the code next. Will stop when an `else` or `end` is found. | `if *IDN,OK`          |
| `else`      | `else`               | End an `if` condition, and only evaluate if the first condition was false.                               | `else`                |
| `end`       | `end`                | Any condition, regardless of the initial evaluation                                                      | `end`                 |
| `print`     | `print <string>`     | Print the passed string to the console.                                                                  | `print Hello World !` |
| `increment` | `increment <target>` | Increment the target variable (pass or fail). Can be used to track success or fails.                     | `increment pass`      |

### Variables

The internal sequence engine does not support user variables. There air only two of these : pass and fail. 
For a sequence to return 0 (success), `pass > 0` and `fail = 0`.

### Structures

The internal sequence engine does only support comparison to the passed string, and the latest result. 
This one is stored within the internal memory of the interpreter.

<div style="background-color: #fff3e0; border-left: 4px solid #ef6c00; padding: 12px; margin: 15px 0; border-radius: 4px;">
  <strong style="color: #ef6c00; display: block; margin-bottom: 6px;">⚡ CAUTION</strong>
  The internal engine does not support any control flow loops or branch jumps. If loops are required, you must use external sequencing.
</div>

## External sequencing

The external sequencing come to address all the limitations of the internal sequencing. And, the good news is that they're complementary !

The external sequencing can be done with **any** tools that support SCPI or telnets commands, thus, [Python](https://www.python.org/) with [pyvisa](https://pyvisa.readthedocs.io/en/latest/), [LabView](https://www.ni.com/fr/shop/labview), and others !

For the greatest implementation, you can use the Desktop App, which include a Python interpreter, as well as a pre-intergated C++ Python library, 
which does all the heavy lifting for you ! Remains the pleasure of typing commands, with the probe class (`probe.send("uart", 0x42)`). 
You can still use the standard library of your system, thus, numpy, matplotlib, and others !

And, as announced, you can use the `probe.run("flash.seq")` to run an internal sequence ! You're getting the best of both worlds : The ideal scripting ability of Python with the performance of custom sequences !
