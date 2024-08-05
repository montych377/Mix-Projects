#define _XTAL_FREQ 8000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

void SPI_Initialize( void ){
    TRISC3 = 0;
    TRISC5 = 0;
    SSPSTAT = 0b00000000;
    SSPCON = 0b00100000;
}
void SPI_tx(char data) {
    SSPBUF = data;  
    while (!SSPSTATbits.BF); 
}
char SPI_rx() {
    while (!SSPSTATbits.BF);  // Wait for reception to complete
    char data= SSPBUF;
    return data;  // Return received data from SPI buffer
}

void main() {
    SPI_Initialize();
    while(1) {
        SPI_tx('A');
        __delay_ms(1000);
    }
}

