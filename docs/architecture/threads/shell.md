# Shell handler

This process, without being one to be properly speaking is a tool that has one job : Identify commands, and sanitize the input stream.
It'll send the command once a `\n` char has been found. This free some ressources for the command parser.

This utility is directly runned by the calling procedure, which can be both sides.