#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main()
{
    DDRD = 0x01;// Set pin Input and Output
    while(1)
    {
        PORTD = 0x01;// set Pin High Low
        _delay_ms(100);
        PORTD = 0x00;
        _delay_ms(100);
    }
}
