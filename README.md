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
