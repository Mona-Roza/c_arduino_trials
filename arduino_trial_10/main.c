/* 
# TIMERS / COUNTERS:

- Timer'lar basit sayaç devreleridir.

- Atmega328p'de 3 adet timer modülü vardır:

        -Timer0 Register: 8 bittir, max alabileceği 255'tir.

        - Timer1 Register: 16 bittir, max alabileceği 65535'tir.

        - Timer2 Register: 8 bittir, max alabileceği 255'tir.

!!! Timer0 ve Timer2 daha kısa süreli zamanlar için işimize yarar.
Özellikle Timer2'nin geniş bir alana hitap etmesinden dolayı çok
kısa süreler için Timer2 daha kullanışlıdır ve daha çok kullanı-
lır.
Timer1 ise daha uzun sürelere hitap eder. 

!!! 16 000 000 frekanslı bir MCU, 250'lik bir counter vasıtasıyla 
16 000/250'den mili saniyede 64 tane işlem yapar.

!!! Dolup sıfırlama da PWM (Pulse With Modulation)'de de (Darbe Ge-
nişlik Modülasyonu) görülür.

!!! Timer'lar CPU'dan bağımsız çalışırlar.

- Timer Clock Time Period: 1/F_CPU'dur. 
(Yani counteri 1 arttırmanın süresi.)

- İstenilen gecikmeyi hesaplamak için:
Formül: Timer count = (Delay / Clock Time Period) - 1

- 16 000 000 F_CPU için 10 ms delayda Timer Count = 39999 clock pulse 
olur. Bu değerleri elimizdeki Timer Registerlerle elde etmek mümkün
olmadığından -tabiiki bunu yazılımda if else kullanarak düzenleye-
biliriz ancak buradaki amacımız hardware yönünden düzenleme yapmak-
bu noktada prescaler kavramı devreye giriyor.

- 8 - 64 - 256 - 1024 -> TC0 & TC1 Prescaler
- 8 - 32 - 64 - 128 - 256 - 1024 -> TC2 Prescaler

!!! Bu prescale değerleri cpu frekansını bölümleyebildiğimiz sınırlardır.

- F_CPU / Precaler_değer şeklinde kullanılır. 

!!! Burada CPU hızını yavaşlatmıyoruz, timer'a giren referans fre-
kansı düşürüyoruz.

- Buradan hesaplama yapmak için;
Formül: Timer Count = (Delay / (Clock Time Period * Prescale_Val)) - 1

!!! Prescaling arttıkça, Resolution düşer. Bu nedenle Prescale de-
ğerlerini bol keseden kullanmamak, hesaplamalarla kullanmak gerekir.

## Timer0:

- Timer0 için, TCCR0A ve TCCR0B (Timer/Counter Control Register) olmak
üzere 2 tane registeri vardır.

        Adres   7       6      5        4       3       2       1       0   

TCCR0A: 0x44 COM0A1  COM0A2  COM0B1  COM0B0     -       -     WGM01   WGM00    

TCCR0B: 0x45 FOC0A   FOC0B     -        -     WGM02    CS02   CS01    CS00

- WGM00 ve WGM01-> (Wawe Form Generation Mode) Timer'in çalışma modunu
belirlerler. WGM02 ile kombine edilerek kullanılır. 

- CS00, CS01, CS01 -> (Clock Select) Birleştirilerek kullanacağız. Dur-
durma, çalıştırma gibi işlemleri yaptırırız. İlgili prescalingler ile
değerler işlenebilir veya prescaling olmadan değerler işlenebilir.

- Timer0 ve Timer2, TCNT0 (Timer/Counter Register) içinde sayar. Yani
counterin olduğu 8 bitlik memory alanıdır.

- No Prescaling:
Timerler genel anlamda sınır değerlerine kadar sayarlar, sınır de-
ğerlerine geldiklerinde bir OVERFLOW FLAG döndürerek sıfırlanırlar.

-Normal Mode with Prescale, prescale değeri x olsun, clk pulse x ka-
dar attığında timer pulse 1 atar. Böylelikle clk/x kadar değer arttı-
rımı yapılarak clk küçük bir alanda kontrol edilmiş olur.

- CTC (Clear Timer on Compare Match Mode with Prescale), OCRnx regis-
terine bir değer verilir, Timer Counter bu değerle eşleştiği anda sı-
fırlanır. Belirli bir sayma (top) değeri vermek yerine, şurada kes 
demiş oluyoruz.
*/

/*
TCCR0A: 0x44 COM0A1  COM0A2  COM0B1  COM0B0     -       -     WGM01   WGM00    

TCCR0B: 0x45 FOC0A   FOC0B     -        -     WGM02    CS02   CS01    CS00
*/
#include <stdint.h>

#define REG_ADDR_TCCR0                  0x44
#define _REG_TCCR0                      (*(volatile uint16_t*)REG_ADDR_TCCR0)
//!!! Burada uint16_t kullanılmasının amacı TCCR0A ile TCCR0B'yi bir-
//!!! leştirerek tek bir yapı kurmaktır.

typedef struct 
{
        uint8_t wgmA:2;
        uint8_t reservedA:2;
        uint8_t com0B:2;
        uint8_t com0A:2;
        uint8_t clock_select: 3;
        uint8_t wgmB:1;
        uint8_t reservedB: 2;
        uint8_t foc0B:1;
        uint8_t foc0A: 1;

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
#define _REG_TCINT0                     (*(volatile uint8_t*) REG_ADDR_TIFR0)

typedef struct 
{
        uint8_t value:8;

}tcnt0_t, *tcnt0_ptr_t;

#define REG_TIMER0_COUNTER                      (*(tccr0_ptr_t) REG_ADDR_TCINT0)
#define TIMER0_COUNTER                          REG_TIMER0_COUNTER.value

typedef struct 
{
        uint8_t tov0:1; 
        uint8_t ocf0a:1;
        uint8_t ocf0b:1;
        uint8_t reserved:5;
}tifr0_t, *tifr0_ptr_t;

#define REG_TIFR0                               (*(tifr0_ptr_t) REG_ADDR_TIFR0)
#define TIMER0_OVERFLOW                         REG_TIFR0.tov0

//timer0_counter -> 0,1,2,....,255 -> timer0_overflow = 1
//ISR -> timer0_overflow = 0
//timer0_overflow = 1
//volatile uint8_t overflow = 0;
//Her taşma sonrası overflow++
//if ile  soruşturmalar.

int main(){
        TIMER0_MODE_SELECTION = TIMER0_mode_NORMAL;
        TIMER0_CLOCK_SELECTION  = TIMER0_ON_no_prescaling;
}

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
leridir.
*/