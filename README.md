# Arduino-in-C
This is a project that I've been working on to start getting a better idea of how the arduino works under the hood of the arduino ide. The first thing I plan on doing is making a header file for each of the common commands in .io, but in the C language. More specifically in AVR-C. With each command I'll walk through exactly how it works in the comments and an accompaning ReadMe.md file. The point of this project is to learn rather than create something new. Once I'm done I hope for this repository to be a nice path for anyone else that wants to dive a little bit deeper into the arduino and other AVR micro controllers. 

# Getting Started
The first thing that you need to do to get started is to download and install the arduino ide. By installing the arduino IDE you are also installing every dependency you need to upload your C code to the ATmega/Arduino without the ide. Then plug in your arduino and set up the blink program (File->Examples->01.Basics->Blink) as you would normally do. 

Before uploading the Blink.io sketch you need to turn on "verbose output" first. This will tell you everything the arduino ide is doing to upload your program to the arduino. The "verbose output" option is not on by default. To turn it on go to Preferences or hit (Ctrl + ,) for windows and linux, or (Alt + ,) for Mac. 



Now, upload the Blink.io program to the board and you should see the following output:
