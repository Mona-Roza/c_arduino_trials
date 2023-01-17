### Devre Şeması:

[](https://github.com/Mona-Roza/c_arduino_trials/blob/main/arduino_trial_7/circuit_diagram.png)

### Seven Segment Display:

[![](https://github.com/Mona-Roza/c_arduino_trials/blob/main/arduino_trial_7/seven_segment_display.png)](https://github.com/Mona-Roza/c_arduino_trials/blob/main/arduino_trial_7/seven_segment_display.png)

:warning: Seven segment display'in sıralı pinleri Arduino'nun sıralı pinlerine takılmalıdır.

### Derleme:

``` 
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c

avr-gcc -mmcu=atmega328p main.o -o main

avr-objcopy -O ihex -R .eeprom main main.hex
```

### Yükleme:

```
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
```
### [Tinkercad](https://www.tinkercad.com/things/kQyTbtTztz1) üzerinden simüle edebilirsiniz.
