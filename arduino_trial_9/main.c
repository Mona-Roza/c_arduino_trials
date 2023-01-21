#include <stdint.h>
#include <avr/interrupt.h>
#include "_328p_gpio.h"

#define REG_ADDR_PCICR          0x68
#define REG_PCICR               ((pcicr_ptr_t) REG_ADDR_PCICR)

#define REG_ADDR_PCMSK0         0x68
#define REG_PCMSK0             ((pcmsk0_ptr_t) REG_ADDR_PCMSK0)

#define REG_ADDR_PCMSK1         0x6C
#define REG_PCMSK1             ((pcmsk1_ptr_t) REG_ADDR_PCMSK1)

#define REG_ADDR_PCMSK2         0x6D
#define REG_PCMSK2              ((pcmsk2_ptr_t) REG_ADDR_PCMSK2)

typedef struct 
{
    uint8_t pcie0:1;
    uint8_t pcie1:1;
    uint8_t pcie2:1;
    uint8_t reserverd:5;
}pcicr_t, *pcicr_ptr_t;

typedef struct 
{
    uint8_t pcint0:1;
    uint8_t pcint1:1;
    uint8_t pcint2:1;
    uint8_t pcint3:1;
    uint8_t pcint4:1;
    uint8_t pcint5:1;
    uint8_t pcint6:1;
    uint8_t pcint7:1;
}pcmsk0_t, *pcmsk0_ptr_t;

typedef struct 
{
    uint8_t pcint8:1;
    uint8_t pcint9:1;
    uint8_t pcint10:1;
    uint8_t pcint11:1;
    uint8_t pcint12:1;
    uint8_t pcint13:1;
    uint8_t pcint14:1;
    uint8_t reserved:1;
}pcmsk1_t, *pcmsk1_ptr_t;

typedef struct 
{
    uint8_t pcint16:1;
    uint8_t pcint17:1;
    uint8_t pcint18:1;
    uint8_t pcint19:1;
    uint8_t pcint20:1;
    uint8_t pcint21:1;
    uint8_t pcint22:1;
    uint8_t pcint23:1;
}pcmsk2_t, *pcmsk2_ptr_t;


#define PCINT_ENABLE 1

ISR(PCINT0_vect){
    
}

int main()
{

    REG_PCICR->pcie0 = PCINT_ENABLE;
    REG_PCMSK0->pcint0 = PCINT_ENABLE;
    sei();
}