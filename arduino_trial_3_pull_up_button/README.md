### Devre Şeması:

[![](https://github.com/Mona-Roza/c_arduino_trials/blob/main/ardunio_trial_3_pull_up_button/circuit_diagram.png)](https://github.com/Mona-Roza/c_arduino_trials/blob/main/ardunio_trial_3_pull_up_button/circuit_diagram.png)

### Derleme :
``` 
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c

avr-gcc -mmcu=atmega328p main.o -o main

avr-objcopy -O ihex -R .eeprom main main.hex
```

### Yükleme
```
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
```
