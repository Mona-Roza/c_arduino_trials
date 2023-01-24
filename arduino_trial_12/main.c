#include "_328p_config.h"
#include <avr/interrupt.h>

static void gpio_init();
static void timer0_init();

volatile uint16_t overflow;
volatile uint8_t  led_no;

int main(){

        gpio_init();
        timer0_init();  

        overflow = 0;
        led_no = 0;

        while(1){

                //do something...
        }
}

static void gpio_init(){
        DDRD_UNION.port = PORT_ALL_OUTPUT;
        PORTD_UNION.port = PORT_ALL_LOW;
}

#define reset_TIMER0_COUNTER

static void timer0_init(){
        TIMER0_MODE_select = timer0_mode_NORMAL;
        TIMER0_CLOCK_select = timer0_no_prescaling_START;
        TIMER0_counter = reset_TIMER0_COUNTER;
        //TIMER0_mode_NORMAL_no_prescaling();

}