
// FOR F_CPU = 1Mhz amd P = 32  Req Delay  = 1 ms 


//#define _XTAL_FREQ 1000000UL
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
//char value = 0;
//#define SBIT_PS2  2
//volatile uint16_t counter = 0;
//
//void __interrupt() timer_isr()
//{  
//    if(TMR0IF==1)
//    {
//        counter++;
//        if(counter == 498){
//            
//            PORTD ^= 0x01;
//            counter = 0;
//        }
//        TMR0 = 249;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
//                          TImer0 needs two instruction Cycles to start incrementing TMR0 */
//        TMR0IF=0;        // Clear timer interrupt flag
//    } 
//     
//}
//
//
//void main()
//{    
//    TRISD=0x00;    //COnfigure PORTD as output to blink the LEDs
//    PORTD = 0x00;
//    OPTION_REG = (1<<SBIT_PS2);  // Timer0 with external freq and 32 as prescalar
//    TMR0=249;       // Load the time value for 1ms delay
//    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
//    GIE=1;          //Enable Global Interrupt
//    PEIE=1;         //Enable the Peripheral Interrupt
//
//    while(1)
//    {
//        
//        
//    }
//}



// FOR F_CPU = 8Mhz amd P = 128  Req Delay  = 5 ms 



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

volatile uint16_t counter = 0;

void __interrupt() timer_isr()
{  
    if(TMR0IF==1)
    { 
        PORTD ^= 0x01;
        TMR0 = 178;     /*Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the*/
        counter++    ;            /* TImer0 needs two instruction Cycles to start incrementing TMR0 */
        TMR0IF=0;        // Clear timer interrupt flag
    } 
     
}


void main()
{    
    TRISD=0x00;    //COnfigure PORTD as output to blink the LEDs
    PORTD = 0x00;
    OPTION_REG = 0x06;
    TMR0=178;       // Load the time value for 1ms delay
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt

    while(1)
    {
        if(counter == 100) {
            
          PORTD ^= 0x02;
          counter = 0;
        }
    }
}