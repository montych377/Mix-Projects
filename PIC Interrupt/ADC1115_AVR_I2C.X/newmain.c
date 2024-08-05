#include "HEADER.h"
#include "I2C_MASTER.h"
#include "ADS1115.h"

void LCD_Command(char cmd);
void LCD_Data(char data);
void LCD_Initialize( void );
void LCD_String(const char *ptr);

int main() {
    char arr1[20] = {0};
    LCD_Initialize();
    I2C_MasterInitialize();
    while(1) {
   
        uint16_t data0 = ADS1115_ReadMultiChannel(ADS1115_ADDR_GND,0x00,0);
        _delay_ms(1);
        sprintf(arr1,"ADC AN0 : %05d",data0);
        LCD_Command(0x80);
        LCD_String(arr1);
      
    }
}
void LCD_Command(char cmd) {
    
    PORTB = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Data(char data) {
    
    PORTB = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Initialize( void ) {
    
    DDRB = 0xFF;
    DDRC = 0x0F;
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
