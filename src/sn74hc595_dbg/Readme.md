SN74HC595 based debugger for the PIC12F675
==========================================

This example provides a simple "debugger" based on the SN74HC595
shift-register. In this scenario the pic needs two GPs to clock out
data to the shift-register IC. Connecting eight leds to the IC you
can display whole bits. If you chain two 595 together, you can display
16 bit words.

![](schematic.png)

To save a GP-line, we don't bother to clock out from serial-register
to parallel-register. Instead we connect SRCLK and RCLK. This needs an
additional clock-cycle for the last bit, i.e. the pic sends 9 bits
in total. With two connected 595-ICs, the pic sends 17 bits.

The example program waits for a button-press on GP5 and then displays
and increasing counter. It stops again once the counter wraps around to
zero or if the button is pressed again.
