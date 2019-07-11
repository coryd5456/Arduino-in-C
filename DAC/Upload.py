import os

filename = "DAC"

os.system("avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o "+filename+".o "+ filename +".c \n")
os.system("avr-gcc -mmcu=atmega328p "+filename+".o -o "+filename+" \n")
os.system("avr-objcopy -O ihex -R .eeprom "+filename+" "+filename+".hex \n")
os.system("avrdude -F -V -c arduino -p ATmega328P -carduino -P/dev/ttyUSB0 -b57600 -D -U flash:w:"+filename+".hex")
