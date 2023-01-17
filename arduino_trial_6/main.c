//Buton durumunu tutma
#include <avr/io.h>
#include<util/delay.h>

#ifndef F_CPU
#define F_CPU   16000000UL
#endif

#define BUTTON_D7_PRESSED           (PIND & 1<<7)
#define STATE_ON                    1
#define STATE_OFF                   0
#define DELAY_TIME                  300
#define LEDS_ON                     (PORTB = 0xFF)
#define LEDS_OFF                    (PORTB = 0x00)

int main(){
    DDRB = 0xFF;
    DDRD = 0x7F;
    PORTB = 0x00;

    uint8_t _state =0;

    while(1){
        if((STATE_ON == _state) && BUTTON_D7_PRESSED){
            _state = 0x00;
            _delay_ms(DELAY_TIME);
        }
        else if((STATE_OFF == _state) && BUTTON_D7_PRESSED){
            _state = 0x01;
            _delay_ms(DELAY_TIME);
        }

        if(_state & (0x01)){
            LEDS_ON;
        }else{
            LEDS_OFF;
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