# TM4C123GH6PM

# TM4C123GH6PM-GPIO
GPIO driver for TI TM4C123GH6PM. Written using KEIL v5.24a and compiled with ARM Compiler v6. Debbugged and Tested using TIVA C LaunchPad board.

## Specifications
*  Uses CMSIS for register acesses.
*  Uses Bit addressing.
*  Doesn't unlock device pins that requires special considrations ('JTAG and NMI').
*  Doesn't handle interrupts ('To be added').

## Notes
1.  Functions descriptions are in the header file.

## TM4C123GH6PM Delay
Delay functions based using timers. Written using CCS and compiler with TI compiler.
## Specifications
* Uses TivaWare Library v2.1.4
* Selectable timer module
* Almost 100% accurate using stop watch.
## Notes
1. Functions descriptions are in the .h file.
2. Select the required timer module and CPU frequency in CPU_FREQ and TIMER_BASE macros.
