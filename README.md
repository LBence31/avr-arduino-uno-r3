# AVR Arduino Uno R3 Programming

_Learning the basics of embedded programming with AVR on an Arduino Uno R3 which has an ATmega328P microcontroller._


The projects are from the "Projects Book" from the Arduino Starter Kit. The code might not do exactly what the book expects, as I'm actively trying to play around and test things.

There is also a picture for each project describing the circuit. If there isn't one, then no circuit is needed, as in `01_Blink` project, which simply blinks the onboard LED.

I'm not using the Arduino IDE to implement the code; instead I'm using "pure C" to write code for the hardware. I'm still using the Arduino bootloader because the main reason for this repo/project is to explore embedded programming with only the basics.

## Workflow

I'm working on Fedora Linux (via WSL) and here are the packages and programs I'm using for my "pure C" workflow:

- avr-gcc - compiler for the AVR microcontrollers
- avr-libc - standard C library for AVR
- avrdude - flash/uploader to talk to the bootloader (or programmer)
- make - to simplify the build process
- screen - for serial monitoring, aka debug
- [usbipd-win tool](https://github.com/dorssel/usbipd-win/releases) - installed on windows to share the board connected via USB to WSL2
- vim (btw)
