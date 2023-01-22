/*
PIN CHANGED INTERRUPTS:

Arduino'da 22 adet Pin'de PCI (Pin changed Interrupts) kullana-
biliyoruz. 

Bunlar, ilk başta PCICR (Pin Change Interrupt Control Register)
ile yönetiliyor. 

PCICR Register'inin 0. biti 0 ile 7. pin arasını, 1. biti 8 ile 14.
pin arasını, 2. biti ise 16 ile 23. pin arasını kullanmamızı sağlar

!!! PCICR ile 15. pini kontrol edemeyiz, çünkü reserve'lidir.

PCMSK olarak 3 tane Pin Change Mask Registeri vardır.

PCMSK0 -> 0-7 arasını
PCMSK1 -> 8-14 arasını
PCMSK2 -> 16-23 arasını

açıp kullanmamızı sağlar.
*/

#include <stdint.h>
#include <avr/interrupt.h>
#include "_328p_gpio.h"

#define REG_ADDR_PCICR          0x68
#define REG_PCICR               ((pcicr_ptr_t) REG_ADDR_PCICR)

#define REG_ADDR_PCMSK          0x6B
#define REG_PCMSK               ((pcmsk_ptr_t) REG_ADDR_PCMSK)



// PCIR'nin modellemesi 
typedef struct 
{
    uint8_t portB:1;    //PCICR 0. Enable Biti 
    uint8_t portC:1;    //PCICR 1. Enable Biti 
    uint8_t portD:1;    //PCICR 2. Enable Biti 
    uint8_t reserverd:5;
}pcicr_t, *pcicr_ptr_t;


// PCMSK0, 1, 2'nin birlikte modellemesi 
//Burada register adreslerimiz ardışık olduğu için tek structta ta-
//nımladık
typedef struct 
{
    uint8_t pcint_pb0:1;
    uint8_t pcint_pb1:1;
    uint8_t pcint_pb2:1;
    uint8_t pcint_pb3:1;
    uint8_t pcint_pb4:1;
    uint8_t pcint_pb5:1;
    uint8_t reserved1:2; 
    uint8_t pcint_pc0:1;
    uint8_t pcint_pc1:1;
    uint8_t pcint_pc2:1;
    uint8_t pcint_pc3:1;
    uint8_t pcint_pc4:1;
    uint8_t pcint_pc5:1;
    uint8_t pcint_pc6:1;
    uint8_t reserved2:1;
    uint8_t pcint_pd0:1;
    uint8_t pcint_pd1:1;
    uint8_t pcint_pd2:1;
    uint8_t pcint_pd3:1;
    uint8_t pcint_pd4:1;
    uint8_t pcint_pd5:1;
    uint8_t pcint_pd6:1;
    uint8_t pcint_pd7:1;
}pcmsk_t, *pcmsk_ptr_t;

#define PCINT_ENABLE 1
#define PCINT_PB_vect           PCINT0_vect
#define PCINT_PC_vect           PCINT1_vect
#define PCINT_PD_vect           PCINT2_vect
//B portunun 0. bitini aldığımız için PCINT0 vektörünü aktifleştrdik.
ISR(PCINT_PB_vect){
    PORTD_UNION->port ^= PORT_ALL_HIGH; 
}

int main()
{   
    DDRD_UNION->port = PORT_ALL_OUTPUT;

    REG_PCICR->portB=PCINT_ENABLE;
    REG_PCMSK->pcint_pb5 =PCINT_ENABLE;

    sei(); //SREG registerindeki sei makrosu aktif edildi.
    while(1){

    }
}