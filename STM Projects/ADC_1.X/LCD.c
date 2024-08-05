
#include "LCD.h"

    void LCD_WriteCommand(unsigned char cmd){
        LCD_PORT  = cmd & 0xf0;
        LCD_PORT &= ~(1<<LCD_RS);
        LCD_PORT &= ~(1<<LCD_RW);
        LCD_PORT |=  (1<<LCD_EN);
        _delay_ms(5);
        LCD_PORT &= ~(1<<LCD_EN);
        _delay_ms(5);

        LCD_PORT  = (cmd<<4) & 0xf0;
        LCD_PORT &= ~(1<<LCD_RS);
        LCD_PORT &= ~(1<<LCD_RW);
        LCD_PORT |=  (1<<LCD_EN);
        _delay_ms(5);
        LCD_PORT &= ~(1<<LCD_EN);
        _delay_ms(5);
        
    }

    void LCD_WriteData(unsigned char data){
        LCD_PORT  = data & 0xf0;
        LCD_PORT |= (1<<LCD_RS);
        LCD_PORT &= ~(1<<LCD_RW);
        LCD_PORT |=  (1<<LCD_EN);
        _delay_ms(5);
        LCD_PORT &= ~(1<<LCD_EN);
        _delay_ms(5);

        LCD_PORT  = (data<<4) & 0xf0;
        LCD_PORT |=  (1<<LCD_RS);
        LCD_PORT &= ~(1<<LCD_RW);
        LCD_PORT |=  (1<<LCD_EN);
        _delay_ms(5);
        LCD_PORT &= ~(1<<LCD_EN);
        _delay_ms(5);
    }
    void LCD_Initialize( void ){
        LCD_PORT_DIR = 0xff;
        
        LCD_WriteCommand(0x01);
        LCD_WriteCommand(0x02);
        LCD_WriteCommand(0x06);
        LCD_WriteCommand(0x28);
        LCD_WriteCommand(0x0c);
    }
    void LCD_WriteString(const char *ptr){
        while(*ptr){
            LCD_WriteData(*ptr++);
        }
    }
    void LCD_Location(uint8_t row , uint8_t col){
        if(row == 2){
            LCD_WriteCommand(0xc0 | col);
        }
        else{
            LCD_WriteCommand(0x80 | col);
        }
    }
