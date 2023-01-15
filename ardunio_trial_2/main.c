#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

int main()
{
    // 8, 9, 10, 11 ve 12 numaralı pinler PORTB'ye bağlı
    // 0, 1, 2, 3, 4 numaralı pinlerdir, bu pinleri çıkış
    // olarak ayarlayalım:

    uint8_t leds[] = { PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5};

    DDRB |= 0x1F;
    PORTB = 0x00;
    uint8_t i, j;

    while (1)
    {
        for(i=0, j=5; i<3 && j>2; i++, j--){
            PORTB |= (1<<leds[i]) | (1<<leds[j]);
            _delay_ms(500);
            PORTB &= ~(1<<leds[i]) & ~(1<<leds[j]);
            _delay_ms(500);
        }
        for(i=2, j=3; i<3 && j>2; i--, j++){
            PORTB |= (1<<leds[i]) | (1<<leds[j]);
            _delay_ms(500);
            PORTB &= ~(1<<leds[i]) & ~(1<<leds[j]);
            _delay_ms(500);
        }
    } 
    return 0;
}

/*Derleme :
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex

Yükleme
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
*/