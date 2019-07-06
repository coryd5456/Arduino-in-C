# Arduino-in-C
This is a project that I've been working on to start getting a better idea of how the arduino works under the hood of the arduino ide. The first thing I plan on doing is making a header file for each of the common commands in .io, but in the C language. More specifically in AVR-C. With each command I'll walk through exactly how it works in the comments and an accompaning ReadMe.md file. The point of this project is to learn rather than create something new. Once I'm done I hope for this repository to be a nice path for anyone else that wants to dive a little bit deeper into the arduino and other AVR micro controllers. 

# Getting Started
The first thing that you need to do to get started is to download and install the arduino ide. By installing the arduino IDE you are also installing every dependency you need to upload your C code to the ATmega/Arduino without the ide. Then plug in your arduino and set up the blink program (File->Examples->01.Basics->Blink) as you would normally do. 

Before uploading the Blink.io sketch you need to turn on "verbose output" first. This will tell you everything the arduino ide is doing to upload your program to the arduino. The "verbose output" option is not on by default. To turn it on go to Preferences or hit (Ctrl + ,) for windows and linux, or (Alt + ,) for Mac. 



Now, upload the Blink.io program to the board and you should see the following output:

(file directory to arduino)/arduino-1.8.9/hardware/tools/avr/bin/avrdude -C
(file directory to arduino)/arduino-1.8.9/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:/tmp/arduino_build_43879/Blink.ino.hex:i 

If you enter these commands in the terminal, then it will upload the Blink.ino sketch to your arduino. This essentially is the first step away from the arduino ide. There are some things to notice in these two lines. The first is "avr" and the second is "avrdude". The ATmega series of chips are all designed around an AVR processor. "avrdude" is a C compiler that allows you to interface with the AVR processor in these chips. Essentially, once you learn how to program in the AVR-C library, then you can program any chip that uses an AVR processor not just the arduino. Lets also break down the second line.

avrdude.conf -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600
avrdude.conf -v -p <chip name> -carduino -P <USB Port> -b<Baud Rate or Upload Speed>
  
The line above allows you to select what type of chip you are uploading to, which USB Port it is connect to on your computer, and the speed at which you would like to upload the bit stearm. Note: When I say bit stream, this is the .hex file that your code is compiled to before being flashed to the microcontroller. Each of these you must change to your specific machines preferences. The nice thing is that the arduino IDE does this for you automatically. You can find the chip type by reading the silkscreen (text) on the microcontroller itself. You can also determine which port it's connected to via which port the arduino ide selected upon uploading the Blink.ino sketch. 

Now, we want to upload C files not .ino files. To do this, the arduino ide uses a gcc compiler called avr-gcc. Which you already have installed on your machine since you installed the arduino ide. I created a short python sketch with the different commands that I use to upload my .c code in the terminal. Note, we are still using avrdude to upload the .hex file. The previous 3 lines are used to generate a .hex file from your .c code. The .hex file is specific to the microcontroller you are uploading to. 

import os

filename = "PWM"

os.system("avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o "+filename+".o "+ filename +".c \n")
os.system("avr-gcc -mmcu=atmega328p "+filename+".o -o "+filename+" \n")
os.system("avr-objcopy -O ihex -R .eeprom "+filename+" "+filename+".hex \n")
os.system("avrdude -F -V -c arduino -p ATmega328P -carduino -P/dev/ttyUSB0 -b57600 -D -U flash:w:"+filename+".hex")
