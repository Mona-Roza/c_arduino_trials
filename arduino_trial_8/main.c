// REGISTER MODELLEME VE INTERRUPT 

/*
EIMSK (External Interrupt Mask Register): 

    - Adresi: 0x3D

    - INT0 ve INT1'i açar.

EICRA (External Interrupt Control Register):

    - Adresi: 0x69

    - ISC00, ISC01, ISC10, ISC11 

EIFR (External Interrupt Flag Register):

    - Adresi: 0x3C

    -INTF0 ve INTF1
*/
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "_328p_gpio.h"
#include "_328p_external_inrerrups.h"

#define LOOP_DELAY_MS                100
/***********************Register Modelleme Yapıldı***********************/

static void init_gpio(){
    DDRB_UNION->port = PORT_ALL_OUTPUT;
    PORTB_UNION->port = PORT_ALL_LOW;
    DDRD_UNION->pins.pin6 = PIN_OUTPUT;
    DDRD_UNION->pins.pin7 = PIN_OUTPUT;
}

static void init_external_interrupt(){
    REG_EIMSK->int0 = INTERRUPT_ENABLE;
    REG_EIMSK->int1 = INTERRUPT_ENABLE;

    REG_EICRA->int0_mode = INT_MODE_FALLING_EDGE;
    REG_EICRA->int1_mode = INT_MODE_RISING_EDGE;

    sei();
}

uint8_t i=0;

void loop1(){
    for ( i = 0; i < 6; i++)
    {
        PORTB_UNION->port ^= (1<<i);
        _delay_ms(LOOP_DELAY_MS);
    }
}

void loop2(){
    for ( i = 7; i > 0; i--)
    {
        PORTB_UNION->port ^= (1<<(i-1));
        _delay_ms(LOOP_DELAY_MS);
    }
}

volatile uint8_t selection;

ISR(INT0_vect){
    selection = 1;
    PORTD_UNION->pins.pin6 ^= PIN_HIGH;
}

ISR(INT1_vect){
    selection = 2;
    PORTD_UNION->pins.pin7 ^= PIN_HIGH; 
}

int main(){
    init_gpio();
    init_external_interrupt();
    
    selection = 0;

    while (1)
    {
        switch (selection)
        {
        case 1:
            loop1();
            break;
        
        case 2: 
            loop2();
            break;

        default: 
            break;
        }
    }
    

}