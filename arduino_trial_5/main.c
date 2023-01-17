#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define FCPU 16000000UL
#endif

#define INIT_PORTS()            do{DDRB = 0xFF; DDRD = 0x7F;PORTB = 0x00;} while (0)
    
#define BUTTON_PRESSED          (PIND & 1 << 7)
#define DEBOUNCE_TIME           50
#define LOOP_TIME               100


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

void loop1(), loop2();

void loop1(){

    uint8_t i = 0;

    for(i=0;i<6; i++){
        PORTB ^= (1<<i);
        _delay_ms(LOOP_TIME);
    }
}

void loop2(){

    uint8_t i = 0;

    for(i=6;i>0; i--){
        PORTB ^= (1<<(i-1));
        _delay_ms(LOOP_TIME);
    }
}

int main()
{
    INIT_PORTS();
    void (*fun_ptr_arr[])() = {loop1, loop2};
    uint8_t loop_index = 0;

    while (1)
    {  
        if(state()){
            switch(loop_index){
                case 0:
                    fun_ptr_arr[0]();
                    loop_index+=state();
                    break;
                case 1:
                    fun_ptr_arr[1]();
                    loop_index-=state();
                    break;
            }
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