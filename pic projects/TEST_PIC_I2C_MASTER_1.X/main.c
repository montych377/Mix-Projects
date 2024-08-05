/*
 * File:   main.c
 * Author: Sofcon_Lab2
 *
 * Created on 4 June, 2023, 11:12 PM
 */

#define _XTAL_FREQ 12000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

void lcd_cmd(char cmd){
    PORTD = cmd;
    PORTB &= ~0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(3);
    PORTB &= ~0x04;
    __delay_ms(3);
}

void lcd_data(char data){
    PORTD = data;
    PORTB |= 0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(3);
    PORTB &= ~0x04;
    __delay_ms(3);
}

void lcd_init(){
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
}

void lcd_string(char *ptr){
    while(*ptr){
        lcd_data(*ptr++);
    }
}


void I2C_Initialize(unsigned char c){
    SSPCONbits.SSPEN = 1;
    SSPCONbits.SSPM3 = 1;
    SSPADD = (((_XTAL_FREQ)/(4*c))-1);
 
}

void I2C_Master_Wait(){
    while((SSPSTAT & 0x04)|(SSPCON2 & 0x1f));
}

void I2C_Start(){
    I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
}

void I2C_WriteData(char data){
    
    I2C_Master_Wait();
    SSPBUF = data;
}

void I2C_Stop(){
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;
}

void I2C_WriteSring(const char *ptr){
    while(*ptr){
        I2C_WriteData(*ptr++);
    }
}
int main(void) {
    TRISD = TRISB = 0x00;
    PORTD = PORTB = 0x00;
    char arr[]="HELLO";
    int i=0;
    I2C_Initialize(100);
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Transmit->");
    lcd_cmd(0xc0);
    lcd_string(arr);
    while(1){
        
        I2C_Start();
        __delay_ms(100);
        I2C_WriteData(0x30);
        __delay_ms(100);
        I2C_WriteSring(arr);
        __delay_ms(100);
        I2C_Stop();
        __delay_ms(100);
        
    }
    
    return 0;
}
