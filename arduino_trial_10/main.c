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
(Yani counteri 1 arttırmanınsüresi.)

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

- Timerler genel anlamda sınır değerlerine kadar sayarlar, sınır de-
ğerlerine geldiklerinde bir OVERFLOW FLAG döndürerek sıfırlanırlar.
Prescale kullanıldığında ise, kaçlık bir prescale değer kullanıl-
mışsa clock pulse'un o prescale değerine bölümü kadar sonra flag 
döndürür.

*/
