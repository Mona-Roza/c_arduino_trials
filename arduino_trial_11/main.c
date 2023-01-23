/*
#HESAPLAMALAR:

- F_CPU (Hz)      Required Delay (ms)        Prescaler       Clock Frequency (Pulses/ms)        Resolution (ms)            Software Overflow               Timer Counter Value           
-16000000                 1                                      (F_CPU/prescaler/1000)         (1/Clock Freq.)                    1               (R. Delay/Resolution/Software O.)-1
16000000                  1                      1                      16000                     0,0000625                        1                            15999
16000000                  1                      8                       2000                        0,0005                        1                             1999
16000000                  1                     32                        500                         0,002                        1                              499
16000000                  1                     64                        250                         0,004                        1                              249
16000000                  1                    128                        125                         0,008                        1                              124
16000000                  1                    256                       62,5                         0,016                        1                             61,5
16000000                  1                   1024                     15,625                         0,064                        1                           14,625

!!! 255, 65535 bu değerler alınabilen en küçük ve en büyük counter değer-
leridir. Bu değerleri Timer Counter Value'de sağlayabilmek için software
overflow değerleri ile hesaplama yaparız ve bu software overflow değerle-
riyle kodlama yaparız.
*/

#include <stdint.h>
#include "_328p_gpio.h"
#define USE_GPIO_D


#define REG_ADDR_TCCR0                  0x44
#define _REG_TCCR0                      (*(volatile uint16_t*)REG_ADDR_TCCR0)
//!!! Burada uint16_t kullanılmasının amacı TCCR0A ile TCCR0B'yi bir-
//!!! leştirerek tek bir yapı kurmaktır.

typedef struct 
{
        uint8_t wgmA                    :2;
        uint8_t reservedA               :2;
        uint8_t com0B                   :2;
        uint8_t com0A                   :2;
        uint8_t clock_select            :3;
        uint8_t wgmB                    :1;
        uint8_t reservedB               :2;
        uint8_t foc0B                   :1;
        uint8_t foc0A                   :1;

}_tccr0_t, *_tccr0_ptr_t;


typedef union
{
        _tccr0_t bits;
        volatile uint16_t value;

}tccr0_t, *tccr0_ptr_t;


#define REG_TCCR0_UNION                 (*(tccr0_ptr_t) REG_ADDR_TCCR0)
#define TIMER0_MODE_SELECTION           REG_TCCR0_UNION.bits.wgmA
#define TIMER0_mode_NORMAL              0
#define TIMER0_mode_CTC                 2

#define TIMER0_CLOCK_SELECTION          REG_TCCR0_UNION.bits.clock_select
#define TIMER0_no_clock_source                          0
#define TIMER0_ON_no_prescaling                         1
#define TIMER0_prescaling_8                             2
#define TIMER0_prescaling_64                            3
#define TIMER0_prescaling_256                           4
#define TIMER0_prescaling_1024                          5
#define TIMER0_external_clock_falling_edge              6
#define TIMER0_external_clock_rising_edge               7

#define REG_ADDR_TCINT0                 0x46
#define _REG_TCINT0                     (*(volatile uint8_t*) REG_ADDR_TCINT0)

#define REG_ADDR_TIFR0                  0x35
#define _REG_TIFR0                      (*(volatile uint8_t*) REG_ADDR_TIFR0)

typedef struct 
{
        uint8_t value:8;

}tcnt0_t, *tcnt0_ptr_t;

#define REG_TIMER0_COUNTER                      (*(tccr0_ptr_t) REG_ADDR_TCINT0)
#define TIMER0_COUNTER                          REG_TIMER0_COUNTER.value

uint16_t overflow;
uint8_t led_no;

int main(){
        DDRD_UNION.port = PORT_ALL_OUTPUT;
        TIMER0_MODE_SELECTION = TIMER0_mode_NORMAL;

        // !!! No prescaling'e ait ön kodlar.
        // TIMER0_CLOCK_SELECTION = TIMER0_ON_no_prescaling;
        // TIMER0_COUNTER = 0;
        // overflow = 0;
        // led_no = 0;

        // !!! 64 prescale değeri ile timer kodları:
        TIMER0_CLOCK_SELECTION = TIMER0_prescaling_64;
        TIMER0_COUNTER = 0;

        overflow = 0;
        led_no = 0;

        while(1){
                /*
                !!! No Prescaling kodları bu satırlardır.
                if(TIMER0_COUNTER>=249){
                        overflow++;
                        TIMER0_COUNTER = 0;

                        if (overflow>=8000){
                        !!! 8000 değerini software overflow tablosunda oynama yaparak bulduk  
                                overflow = 0;
                                PORTD_UNION.port = (1<<led_no);
                                led_no++;
                        }
                        led_no = (led_no>7) ? 0: led_no;
                        
                }
                
                * Normal şartlarda, yukarıdaki işlemi yaptırmak, 
                büyük işlemler arasında bir zaman kaybına yol aça-
                cağı için prescale kullanmamız gerekir. Ancak ve 
                ancak yukarıdaki işlem MCU'da çok yük olmadığında
                kullanılabilir.

                - Prescale kullanılarak yapılan işlem aşağıdakine 
                benzer olmalıdır.
                */

                if(TIMER0_COUNTER>=249){
                        overflow++;
                        TIMER0_COUNTER = 0;

                        if (overflow>=50){
                                overflow = 0;
                                PORTD_UNION.port = (1<<led_no);
                                led_no++;
                        }
                        led_no = (led_no>7) ? 0: led_no;
                        
                }

        }
}

