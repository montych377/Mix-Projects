//
//#define XTAL_FREQ 8000000
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
//#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
//#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//
//#include <xc.h>
//
//void Timer1_Init() {
//    
//    T1CONbits.T1CKPS0 = 1;
//    T1CONbits.T1CKPS1 = 1;
//    
//    TMR1L = 0xee;
//    TMR1H = 0x85;
//    
//    PIE1bits.TMR1IE = 1;
//    INTCONbits.PEIE = 1;
//    INTCONbits.GIE = 1;
//    T1CONbits.TMR1ON = 1;
//}
//
//void __interrupt() Timer1() {
//    
//    if(TMR1IF == 1)
//    {
//        PORTD ^= 0xff;
//        TMR1L = 0xee;
//        TMR1H = 0x85;
//        TMR1IF = 0;
//    }
//}
//
//
//int main() {
//    
//    TRISD = 0x00;
//    PORTD = 0x00;
//    Timer1_Init();
//    while(1) {
//        
//        
//    }
//}





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
char value = 0;
void __interrupt() timer1_isr(){
    
    if(TMR1IF==1){
        
        counter1++;
        counter2++;
        PORTD ^= 0x01;
     
        TMR1L = 0xCB;
        TMR1H = 0xF3;
        TMR1IF = 0;
    }
}

void Timer1_init(){
    
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;
    
    TMR1L = 0xCB;
    TMR1H = 0xF3;
    
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;
}
int main() {
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    Timer1_init();
    
    while(1) {
        
        //PORTD = value;
        
        if(counter1 == 5){
            PORTD ^= 0x02;
            counter1 = 0;
        }
        if(counter2 == 10){
            PORTD ^= 0x04;
            counter2 = 0;
        }
    }
    
    
}
