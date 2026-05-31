# Hardware IO

This task has one primary responsibility: managing all serial I/O from and to the DUT (Device Under Test). This thread is arguably one of the most
complex in the system. It must ensure high-speed, non-blocking writes while simultaneously operating in slave or "spy" mode to capture asynchronous
incoming data and stream it to the appropriate target.

To meet these strict timing constraints without overwhelming the CPU, the task heavily relies on Direct Memory Access (DMA) for both transmission and
reception. Rather than using costly byte-by-byte interrupts or inefficient fixed-interval polling, it leverages STM32 hardware-level frame detection to
flush buffers and route packets dynamically.