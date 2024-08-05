#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRD = 0x01;
    
    while(1)
    {
        
        
        PORTD  = 0x01;
        _delay_ms(300);
        PORTD = 0x00;
        _delay_ms(300);
    }
}