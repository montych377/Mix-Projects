#define F_CPU 1000000UL
#include<avr/io.h>
#include<utr/delay.h>
void LCD_and(char cmd)
{
    PORTD = cmd;
    PORTC&=~0X01;
    PORTC&=~0X02;
    _delay_ms(3);
    PORTC&=~0X04;
    _delay_ms(3);
}