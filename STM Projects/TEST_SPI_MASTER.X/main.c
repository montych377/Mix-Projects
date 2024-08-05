/*
 * File:   main.c
 * Author: Sofcon_Lab2
 *
 * Created on 23 May, 2023, 3:16 AM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>

#define SS   PB2
#define MOSI PB3
#define MISO PB4
#define SCK  PB5

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
void SPI_Initialize(){
    DDRB = (1<<MOSI)|(1<<SCK)|(1<<SS);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_Transmit(char data){
    SPDR = data;
    while((SPSR & (1<<SPIF))==0);
}

char SPI_Receive(){
    while((SPSR & (1<<SPIF))==0);
    return SPDR;
}

void SPI_string(const char *ptr){
    while(*ptr){
        SPI_Transmit(*ptr++);
        _delay_ms(10);
    }
}
int main(void) {
    char data[] = "HELLO";
    char data1[5];
    DDRD = 0xff;
    DDRC = 0x07;
    lcd_init();
    SPI_Initialize();
    lcd_cmd(0x80);
    lcd_string("Transmit->");
    lcd_string(data);
    while(1){
        SPI_string(data);
        _delay_ms(200);
        
        for(int i=0;i<5;i++){
            data1[i]=SPI_Receive();
            _delay_ms(10);
        }
        lcd_cmd(0xc0);
        lcd_string(data1);
    }
    return 0;
}
