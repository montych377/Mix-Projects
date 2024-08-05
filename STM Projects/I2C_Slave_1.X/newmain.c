/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 22 May, 2023, 9:35 PM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>


void lcd_cmd(char cmd){
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_data(char data){
    PORTD = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_init(){
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x02);
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
}
void lcd_string(const char *ptr){
    while(*ptr){
        lcd_data(*ptr++);
    }
}
void I2C_S_Init(char address){
    TWAR = address;
}

char I2C_S_Receive(){
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    while((TWCR & (1<<TWINT))==0);
    while((TWSR & (0xf8)) != 0x80);
    return TWDR;
}

void Address_S_Match(){
    while((TWSR & (0xf8)) != 0x60){
        TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        while((TWCR & (1<<TWINT))==0);
    }
}
int main(void) {
    char arr[5];
    DDRD = 0xff;
    DDRB = 0xff;
    DDRC = 0x07;
    I2C_S_Init(0x02);
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Receive->");
    
    while(1){
        Address_S_Match();
        _delay_ms(100);
        for(int i=0;i<5;i++){
            arr[i] = I2C_S_Receive();
        }
        _delay_ms(100);
       lcd_cmd(0xC0);
       lcd_string(arr);
       
    }
    return 0;
}
