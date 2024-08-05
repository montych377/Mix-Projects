#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRD = 0b00001111; 
    
    while(1)
    {
        PORTD = 0b00001111;
        
        _delay_ms(1000);
        PORTD = 0b000000000;
        _delay_ms(1000);
    }
    
    
}















