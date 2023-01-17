#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define FCPU 16000000UL
#endif

#define INIT_PORTS()            do{DDRB = 0xFF; DDRD = 0x7F;PORTB = 0x00;} while (0)
    
#define BUTTON_PRESSED          (PIND & 1 << 7)
#define DEBOUNCE_TIME           50
#define LOOP_TIME               300

uint8_t state();

uint8_t state()
{
    if (BUTTON_PRESSED)
    {
        _delay_ms(DEBOUNCE_TIME);
        if (BUTTON_PRESSED)
        {
            return 1;
        }
    }
    return 0;
}


int main()
{
    INIT_PORTS();
    uint8_t led_no = 1;

    while (1)
    {  
        if(state()){
            switch(led_no){
                case 1:
                    PORTB ^= (1<<0);
                    PORTB ^= (1<<5);
                    break;
                case 2:
                    PORTB ^= (1<<1);
                    PORTB ^= (1<<4);
                    break;
                case 3:
                    PORTB ^= (1<<2);
                    PORTB ^= (1<<3);
                    led_no = 0;
                    break;
            }
            led_no++;
                
            _delay_ms(LOOP_TIME);
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