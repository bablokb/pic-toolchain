About
=====

This is a simple "firmware" for the following setup:

  - The power of a Raspberry Pi is controlled by a PIC using a mosfet.
  - On an external signal (low), the PIC sets the gate of the mosfet
    to high, thus turning on the Pi.
  - Again on an external signal, the PIC requests the Pi to shutdown by
    setting an output pin to high. This pin is connected and monitored
    by the Pi.
  - The Pi now shuts down and at the end sets a pin to high (using the
    overlay `dtoverlay=gpio-poweroff,gpiopin=x` in `/boot/config.txt`).
  - This pin is connected to the PIC and the PIC now sets the gate to low
    thus turning power off.

The simplest "external signal" is a button connected to the PIC and to GND,
but it could also be a RTC-clock (alarm-pin), or e.g. a motion-sensor. 

Note that the program `rpi_mosfet_on_off.c` supports two external signals.
The default pin-configuration can be changed within the program:

 PIN_POWER  GPIObits.GP5
 PIN_PI_OUT GPIObits.GP4
 PIN_SIG2   GPIObits.GP2
 PIN_SIG1   GPIObits.GP1
 PIN_PI_IN  GPIObits.GP0

  - GP0: PIN_PI_IN (connected to the Pi, same pin as in the gpio-poweroff
    overlay)
  - GP1: PIN_SIG1 (first external signal)
  - GP2: PIN_SIG2 (second external signal)
  - GP3: not connected (reset)
  - GP4: PIN_PI_OUT (shutdown-request, monitored by the Pi)
  - GP5: PIN_POWER (connected to the gate of the mosfet)
