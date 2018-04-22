# TM4C123GH6PM-and-STMF103C8
Libraries compatible with both MCUs
# TM4C123GH6PM-GPIO
GPIO driver for TI TM4C123GH6PM and almost portable to STMF10x Device Family pack. Written using KEIL v5.24a and compiled with ARM Compiler. Debbugged and Tested using TIVA C LaunchPad board.

## Specifications
*  Uses CMSIS for register acesses.
*  Uses Bit addressing.
*  Doesn't unlock device pins that requires special considrations ('JTAG and NMI').
*  Doesn't handle interrupts ('To be added').
*  Functions signatures are compitable with STMF10x DFP.

## Notes
1.  Functions descriptions are in the header file.
2.  `GPIO_PinConfigure` function arguments are not compitable between both devices. You must use the right enum values for each device.

## TM4C123GH6PM Delay
Delay functions based using timers. Written using CCS and compiler with TI compiler.
## Specifications
* Uses TivaWare Library v2.1.4
* Selectable timer module
* Accurate time delays 1% error.
## Notes
1. Functions descriptions are in the .h file.
2. Select the required timer module and CPU frequency in CPU_FREQ and TIMER_BASE macros.
