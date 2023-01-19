/***********************Register Modelleme Yapıldı***********************/
#ifndef _328p_EXTERNAL_INTERRUPS_H
#define  _328p_EXTERNAL_INTERRUPS_H

#include <stdint.h>

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

#endif  /* _328p_EXTERNAL_INTERRUPS_H*/