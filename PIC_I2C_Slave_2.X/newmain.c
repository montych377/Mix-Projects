/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 5 June, 2023, 11:31 PM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define _XTAL_FREQ 8000000  // Set the oscillator frequency

volatile char receivedData;  // Variable to store the received data

void I2C_Slave_Init(unsigned short address) {
    SSPSTAT = 0x80;  // Enable Slew Rate Control, other bits are read-only
    SSPADD = address;  // Set the 7-bit slave address
    SSPCON = 0x36;  // Enable I2C, 7-bit address
    SSPCON2 = 0x01;  // Enable clock stretching
    TRISCbits.TRISC3 = 1;  // Set SDA and SCL pins as input
    TRISCbits.TRISC4 = 1;
    SSPCONbits.CKP = 1;  // Release clock

    SSPIF = 0;  // Clear the SSP interrupt flag
    SSPIE = 1;  // Enable the SSP interrupt

    GIE = 1;  // Enable global interrupts
    PEIE = 1;  // Enable peripheral interrupts
}

void __interrupt() ISR() {
    if (SSPIF) {  // Check if SSP interrupt occurred
        if (!SSPSTATbits.R_nW) {  // Check if it's a write operation
            receivedData = SSPBUF;  // Read the received data from SSPBUF
            
        }

        SSPIF = 0;  // Clear the SSP interrupt flag
        SSPCONbits.CKP = 1;  // Release the clock
    }
}

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
void main() {
    TRISB = 0x00;
    TRISD = 0x00;  // Set PORTD as input
    PORTD = 0x00;  // Clear PORTD initially
    PORTB = 0x00;
    
    I2C_Slave_Init(0x30);  // Initialize I2C Slave with a 7-bit address of 0x50
    lcd_init();
    while (1) {
        // Check if data has been received
        if (receivedData >= 'A' && receivedData<='Z' ) {
            lcd_cmd(0x80);
            lcd_data(receivedData);
            //PORTB= receivedData;  // Display the received data on PORTD
            receivedData = 0;  // Reset the received data variable
        }
    }
}