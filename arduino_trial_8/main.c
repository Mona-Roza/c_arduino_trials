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

/***********************Register Modelleme Yapıldı***********************/

#define REG_ADDRESS_OF_EIMSK            0x3D
#define _REG_EIMSK                      (*(volatile uint8_t*) REG_ADDRESS_OF_EIMSK)

#define REG_ADDRESS_OF_EICRA            0x69
#define _REG_EICRA                      (*(volatile uint8_t*) REG_ADDRESS_OF_EICRA)

#define REG_ADDRESS_OF_EIFR             0x3C
#define _REG_EIFR                      (*(volatile uint8_t*) REG_ADDRESS_OF_EIFR)


typedef struct 
{   
    //interrupt 0 ve interrupt 1 için 1'er 
    //bit ayır anlamında
    uint8_t int0:1;
    uint8_t int1:1;
    uint8_t reserved:6;
    // Bu atama yapılmazsa, struct'lar hafızaya atanırken
    //taşma, kayma gibi şeyler yaşanabilir. Bu yüzden 
    //boşluklarıyla birlikte atama yapmalıyız.
}eimsk_t, *eimsk_ptr_t;

/*
normalde main'in içerisinde 
eimsk_t reg_eimsk = (eimsk_ptr_t) REG_ADDRESS_OF_EIMSK;
şeklinde tanımlanacak kod parçası optimizasyona girebilecek
bir kod parçası olduğundan bunun için bir makro atıyoruz
*/
#define REG_EIMSK                ((eimsk_ptr_t)REG_ADDRESS_OF_EIMSK)

#define INTERRUPT_ENABLE              1
#define INTERRUPT_DISABLE             0


typedef struct main
{
    uint8_t int0_mode: 2;
    uint8_t int1_mode: 2;
    uint8_t reserved:4;
}eicra_t, *eicra_ptr_t;

#define REG_EICRA               ((eicra_ptr_t) REG_ADDRESS_OF_EICRA)  

#define INT_MODE_LOW_LEVEL              0
#define INT_MODE_ANY_LOGICAL_CHANGE     1
#define INT_MODE_FALLING_EDGE           2
#define INT_MODE_RISING_EDGE            3

/***********************Register Modelleme Yapıldı***********************/

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