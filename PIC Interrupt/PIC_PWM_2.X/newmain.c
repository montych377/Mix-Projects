

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

int main() {
    char dutyCycle = 0;

    TRISC = 0x00;   // Configure PORTC as output(RC2-PWM1, RC1-PWM2)
    PORTC = 0x00;
    CCP1CON = 0x0F; // Select the PWM mode.
    PR2 = 180;      // Set the Cycle time to 100 for varying the duty cycle from 0-100
    CCPR1L = 50;    // By default set the dutyCycle to 50
    T2CONbits.TMR2ON = 1;


    while (1) {
        for (dutyCycle = 0; dutyCycle < 180; dutyCycle++) // Keep increasing the dutyCyle to increase the brightness of LED
        {
            CCPR1L = dutyCycle;
            __delay_ms(50);
        }

        for (dutyCycle = 180; dutyCycle > 0; dutyCycle--) // Keep reducing the dutyCyle to decrease the brightness of LED
        {
            CCPR1L = dutyCycle;
            __delay_ms(50);
    }
    }
}
