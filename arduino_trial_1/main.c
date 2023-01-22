#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
    /* set pin 5 of PORTB for output*/
    DDRD |= 0xFF;

    while (1)
    {
        /* set pin 5 high to turn led on */
        PORTD |= 0xFF;
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 5 low to turn led off */
        PORTD &= ~0xFF;
        _delay_ms(BLINK_DELAY_MS);
    }
}