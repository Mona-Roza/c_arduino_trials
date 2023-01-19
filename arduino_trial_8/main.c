// REGISTER MODELLEME 01

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
#include "_3280_gpio.h"
#include "_328p_external_inrerrups.h"


/***********************Register Modelleme Yapıldı***********************/

static void init_gpio(){
    
}

static void init_external_interrupt(){
    REG_EIMSK->int0 = INTERRUPT_ENABLE;
    REG_EIMSK->int1 = INTERRUPT_ENABLE;

    REG_EICRA->int0_mode = INT_MODE_LOW_LEVEL;
    REG_EICRA->int1_mode = INT_MODE_ANY_LOGICAL_CHANGE;

    sei();
}


ISR(INT0_vect){

}

ISR(INT1_vect){

}

int main(){
    init_external_interrupt();
}