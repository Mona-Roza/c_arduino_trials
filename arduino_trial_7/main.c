#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU   16000000UL
#endif

#include "seven_segment.h"

#define REG_ADDRESS_OF_DDRD         0x2A
#define REG_ADDRESS_OF_PORTD        0x2B
#define REG_DDRD                    (*(volatile uint8_t*) REG_ADDRESS_OF_DDRD)
#define REG_PORTD                   (*(volatile uint8_t*) REG_ADDRESS_OF_PORTD)
#define PORT_OUTPUT                 0xFF
#define PORT_ALL_LOW                0x00
#define LOOP_DELAY                  500

static void init(){
    REG_DDRD = PORT_OUTPUT;
    REG_PORTD = PORT_ALL_LOW;
}

int main(){
    init();

    uint8_t i;
    while(1){
        for(i = 0; i<NUMBERS_SIZE; i++){
            REG_PORTD = ss_numbers[i];
            _delay_ms(LOOP_DELAY);
        }
        for(i = 0; i<LETTERS_SIZE; i++){
            REG_PORTD = ss_letters[i];
            _delay_ms(LOOP_DELAY);
        }
    }
    return 0;
}

/*
Derleme : 
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex

Yükleme
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
*/