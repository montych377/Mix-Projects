#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h> 


void lcd_cmd(char cmd) {
    
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}
void lcd_data(char data) {
    
    PORTD = data;
    PORTC |= 0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_init() {
    
    DDRD = 0xff;
    DDRC = 0xff;
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
}
void lcd_loc(uint8_t row,uint8_t col) {
    
    if(row == 2) {
        
        lcd_cmd(0xc0 | col);
    }
    
    else{
        
        lcd_cmd(0x80 | col);
    }
}
int main() {
    lcd_init();
    while(1) {
        
        for(int i=0;i<16;i++) {
            
            lcd_loc(1,i);
            lcd_data('A');
            _delay_ms(100);
            lcd_cmd(0x01);
        }
        for(int i=15;i>=0;i--) {
            
            lcd_loc(1,i);
            lcd_data('A');
            _delay_ms(100);
            lcd_cmd(0x01);
        }
    }
}

