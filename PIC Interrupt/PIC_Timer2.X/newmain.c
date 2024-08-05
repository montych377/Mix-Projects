#define _XTAL_FREQ 1000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

volatile uint16_t counter1 = 0;
volatile uint16_t counter2 = 0;
volatile uint16_t counter3 = 0;
void __interrupt() Timer2() {
    
    if(TMR2IF) {
        
        counter1++;
        counter2++;
        counter3++;
        
        TMR2 = 130;
        TMR2IF = 0;
    }
}

void Timer2_Init() {
    
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
    TMR2 = 130;
    PIE1bits.TMR2IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    T2CONbits.TMR2ON = 1;
}
int main() {
    
    TRISD = 0x00;
    PORTD = 0x00;
    Timer2_Init();
    while(1) {
        
        
        if(counter1 == 100){
            
            PORTD ^= 0x01;
            counter1 = 0;
        }
        if(counter2 == 300){
            
            PORTD ^= 0x02;
            counter2=0;
        }
        if(counter3 == 500){
            
            PORTD ^= 0x04;
            counter3 = 0;
        }   
    }
}

