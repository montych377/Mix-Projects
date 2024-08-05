/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 8 June, 2023, 9:29 PM
 */

#define _XTAL_FREQ 12000000
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

volatile char receivedData=0;
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
void I2C_Initialize(char address){
    SSPSTAT = 0x80;  
    SSPADD = address;  
    SSPCON = 0x36;  
    SSPCON2 = 0x01;  
    TRISCbits.TRISC3 = 1;  
    TRISCbits.TRISC4 = 1;
    SSPCONbits.CKP = 1;  

    SSPIF = 0; 
    SSPIE = 1;  

}

char I2C_Read(){
    while(!SSPIF);
    receivedData = SSPBUF;  
    SSPIF = 0;  
    SSPCONbits.CKP = 1;  
    
    return receivedData;
}

char data_clear(char data[]){
    char Rec_data[10];
    for(int i=0;i<5;i++){
        if(data >= 'A' && data <= 'Z'){
            Rec_data[i] = data;
        }
    }
    return Rec_data;
}

void lcd_string(char *ptr){
    while(*ptr){
        lcd_data(*ptr++);
    }
}
void main(void) {
    char arr[10];
    char d[10];
    TRISD = 0x00;
    TRISB = 0x00;
    PORTD = 0x00;
    PORTB = 0x00;
    I2C_Initialize(0x30);
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Receive ->");
    while(1){
        
        for(int i=0;i<6;i++){
            arr[i] = I2C_Read();
        }
        lcd_cmd(0xC0);
        lcd_string(arr);
    
    }
    return;
}
