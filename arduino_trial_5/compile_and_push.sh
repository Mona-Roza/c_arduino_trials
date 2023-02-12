#!/bin/bash

# This script compiles the source code and creates a main file, a main.o file and a main.hex file. After that, it pushes the main.hex file to the Arduino board.

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c

avr-gcc -mmcu=atmega328p main.o -o main

avr-objcopy -O ihex -R .eeprom main main.hex

echo "Compiled and created main.hex file"

avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex

echo "Pushed main.hex file to Arduino board"
