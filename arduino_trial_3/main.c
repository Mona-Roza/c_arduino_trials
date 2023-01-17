#include <avr/io.h>

#define PIN_HIGH        (PIND & (1<<7))
#define PIN_LOW         (!PIN_HIGH)

int main(){
    // 7. pini (D Registerinin 7. biti 
    //ve arduino üzerinde 7 numaralı pin) 
    //Giriş olarak işaretledik.
    DDRD |= 0x7F; 
    
    //B Registerinin tüm bitlerini çıkış
    //olarak işaretledik. (Arduino üze-
    //rinde 13,12,11,10,9,8 numaralı pinler.)
    DDRB |= 0xFF;


    while(1){
        if(PIND & (1<<7)){
            //Eğer Pin D'nin 7. biti 1 ise
            //B portunun 0, 1, 2. bitlerine 5V ver
            PORTB = 0x07;
        }
        else{
            //Değilse B portunun 3, 4, 5. bitlerine
            //5V ver.
            PORTB = 0x38;
        }
    }

}

/*
Derleme : 
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -mmcu=atmega328p main.o -o main
avr-objcopy -O ihex -R .eeprom main main.hex

Yükleme
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbserial-110 -b 115200 -U flash:w:main.hex
*/