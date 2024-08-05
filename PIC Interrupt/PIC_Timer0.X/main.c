#define XTAL_FREQ 1000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

void Timer0_Delay() {
        
        if(INTCONbits.TMR0IF){
            TMR0 = 0;
            INTCONbits.TMR0IF=0;     
        }

}
int main() {
    
    TRISD = 0x00;
    TMR0 = 0;
    while(1) {
        
        PORTD = 0xff;
        Timer0_Delay();
        PORTD = 0x00;
        Timer0_Delay();
    }
}