#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
void LCD_cmd(char cmd)
{
    PORTD = cmd;
    PORTC&=~0X01;
    PORTC&=~0X02;
    PORTC|=0X04;
    _delay_ms(3);
    PORTC&=~0X04;
    _delay_ms(3);
}
void LCD_data (char data)
{
    PORTD= data ;
    PORTC|=0X01;
    PORTC&=~0X02;
    PORTC|=0X04;
    _delay_ms(5);
    PORTC&=~0X04;
    _delay_ms(8);
    
}
void LCD_initalization()
{
    DDRD=0Xff;
    DDRC=0X07;
    LCD_cmd(0X01);
    LCD_cmd(0X02);
    LCD_cmd(0X06);
    LCD_cmd(0X38); 
    LCD_cmd(0X0C);
      
}
int main()
{
    LCD_initalization();
    while(1)
    {
        LCD_cmd(0X80);
        LCD_data('A');
    }
        
    }
