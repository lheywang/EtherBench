# Sequences

Theses enable advanced interractions with the DUT, including programming them, 
and testing them with a single button press !

## Principle : 
Text file, each line is an instruction or nothing. Sequences can only be fetched from the flash.
\# are comments. 

Cpu will read, line by line and execute or not the instructions.
Only basic conditions are supported.


## Instructions :

- EXEC\["any command supported" \] COND\["test the last value, returned by EXEC. Only string comparison are supported" \] : Will execute, or not some instructions.
- ELSE\[\] : Executed when a cond is evaluted as false
- ENDC\[\] : End of conditions, back to standard flow
- PRTN\[\] : Show in console the text. For avandced logging, configure SPY modile.
- INCR\[PASS | FAIL\] : increment internal variables.