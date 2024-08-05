
#define _XTAL_FREQ 8000000UL

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define BAUDRATE 9600
volatile unsigned char arr[] = "HELLO\r\n";
volatile uint8_t counter =0;

void UART_Initializer(unsigned long baud){
    
    SPBRG = (((_XTAL_FREQ)/(16*baud))-1);
    TXSTA = 0x24;
    RCSTA = 0x90;
    PIE1bits.TXIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
   
}

void send_string(){
    TXREG = arr[counter];
        counter++;
        if(counter == 7){
            
            counter = 0;
        }
}
void __interrupt() UART_TX() {
    
    
    if(TXIF == 1){
        
        send_string();
        __delay_ms(10);
        TXIF =0;
    }
}


int main(){
    
    UART_Initializer(BAUDRATE);
    while(1) ;
}