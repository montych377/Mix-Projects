#include "LCD.h"


void LCD_Command(char cmd) {
    
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Data(char data) {
    
    PORTD = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Initialize( void ) {
    
    DDRD = 0xFF;
    DDRC = 0xFF;
    LCD_Command(0x01);
    LCD_Command(0x02);
    LCD_Command(0x06);
    LCD_Command(0x38);
    LCD_Command(0x0C);
}
void LCD_String(const char *ptr) {
    
    while(*ptr != '\0') {
        
        LCD_Data(*ptr++);
    }
}
void LCD_Location(uint8_t row, uint8_t col) {
    
    if(row == 2) {
        LCD_Command(0x0C | col);
    }
    
    else { 
        LCD_Command(0x80 | col);
    }
}
