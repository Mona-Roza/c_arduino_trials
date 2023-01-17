#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

int main()
{
    // 8, 9, 10, 11, 12 ve 13 numaralı pinler PORTB'ye bağlı
    // 0, 1, 2, 3, 4 numaralı Port B Registeri bitleridir,
    // bu bitleri çıkış (1) olarak ayarlayalım:

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
